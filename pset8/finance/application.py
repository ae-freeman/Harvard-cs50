import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks_owned = db.execute("SELECT symbol, SUM(amount) FROM transactions WHERE user_id = :user_id AND type = 'Buy' GROUP BY symbol;", user_id=session["user_id"])
    print(stocks_owned)

    stock_list = []
    total_value = 0
    for stock in stocks_owned:
        symbol = stock["symbol"]
        amount = stock["SUM(amount)"]
        current_price = (lookup(symbol))["price"]

        stock_data = {}
        stock_data["symbol"] = symbol
        stock_data["amount"] = amount
        stock_data["current_price"] = current_price
        stock_data["total_value"] = current_price * amount

        stock_list.append(stock_data)
        total_value += (current_price * amount)


    #select users available cash
    current_cash_list = db.execute("SELECT cash FROM users WHERE id = :user_id;", user_id=session["user_id"])
    current_cash_value = (current_cash_list[0]["cash"])

    #calculate available cash plus value of their stocks
    grand_total = total_value + (current_cash_list[0]["cash"])
    grand_total_2dp = "%.2f" % grand_total


    return render_template("index.html", stocks = stock_list, cash = current_cash_value, grand_total = grand_total_2dp)
    # return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # shares = request.form.get("shares")


        try:
            numberShares = int(request.form.get("shares"))
        except ValueError:
            return apology("shares must be a positive integer", 400)

        if numberShares < 0:
            return apology("Shares must be a positive integer", 400)

        if not numberShares:
            return apology("Please insert number of shares")


        requestedStock = lookup(request.form.get("symbol"))
        if not requestedStock:
            return apology("Invalid symbol")

        totalCost = numberShares * requestedStock["price"]
        symbol = requestedStock["symbol"]
        price = requestedStock["price"]


        #select users money
        userCashList = db.execute("SELECT cash FROM users WHERE id = :user_id;", user_id=session["user_id"])
        availableMoneyDict = userCashList[0]
        moneyInt = availableMoneyDict["cash"]


        #check if users money is greater than or equal to totalCost
        if moneyInt >= totalCost:
            print("money available")
            newCash = moneyInt - totalCost
            print(newCash)

            #update db with availableMoney - totalCost
            db.execute("UPDATE users SET cash= :newCash WHERE id = :user_id;", newCash=newCash, user_id=session["user_id"])

            now = datetime.now()
            print(now)

            #insert into new table information about the transaction
            db.execute("INSERT INTO transactions (user_id, symbol, price, amount, new_cash, type) VALUES (:user_id, :symbol, :price, :amount, :new_cash, :type)",
            user_id=session["user_id"], symbol=symbol, price=price, amount=numberShares, new_cash=newCash, type="Buy")


        else:
            return apology("Insufficient funds")

        return render_template("index.html")

    else:

        return render_template("buy.html")



@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    username_to_check = request.args.get("username")
    if len(username_to_check) < 1:
        return jsonify(False)

    current_users = db.execute("SELECT username FROM users")

    for user in current_users:
        if user["username"] == username_to_check:
            return jsonify(False)
        else:
            return jsonify(True)



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    rows = db.execute("SELECT * FROM transactions WHERE user_id = :user_id;", user_id = session["user_id"])

    return render_template("history.html", rows = rows)
    # return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():

#User reached route via POST
    if request.method == "POST":
        #     """Get stock quote."""


        #get users request, pass into lookup function, and then save result of lookup function.
        stockSymbol = lookup((request.form.get("symbol")))

        if not stockSymbol:
            return apology("Invalid symbol")


        return render_template("quoted.html", stockSymbol = stockSymbol)


    #User reached route via GET
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])

def register():
    """Register user"""

    #User reached route via POST
    if request.method == "POST":

        #User entered username
        if not request.form.get("username"):
            return apology("must provide username")

        #User entered password
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("must provide password")

        #Confirm password matches
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("password must match")

        #Hash the password
        hash = generate_password_hash(request.form.get("password"))

        #Insert user into database
        result = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                            username=request.form.get("username"), hash=hash)

        if not result:
            return apology("username already exists")
        else:
            return apology("registration complete", 200)

        #Remember user
        session["user_id"] = result

        return redirect("/")

    #User reached route via GET
    else:
        return render_template("register.html")




@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        #get list of stock symbols for the select list
        available_stocks = db.execute("SELECT DISTINCT symbol FROM transactions WHERE user_id = :user_id;", user_id=session["user_id"])
        return render_template("sell.html", stocks = available_stocks)

    else:
        #sell stocks

        #Form Values
        selected_symbol = request.form.get("symbol")



        if selected_symbol == None:
            return apology("Symbol does not exist")


        number_shares = request.form.get("shares")

        if int(number_shares) < 1:
            return apology("Number of shares must be a positive integer")

        print(number_shares)

        #Check how many shares user has of that symbol
        available_shares = db.execute("SELECT SUM(amount) FROM transactions WHERE symbol = :symbol AND user_id = :user_id;", symbol = selected_symbol, user_id=session["user_id"])
        available_shares_number = (available_shares[0]["SUM(amount)"])

        #Check they chose an available number of shares to sell
        if float(number_shares) > available_shares_number:
            return apology("Insufficient shares")

        #Get price of shares
        current_price = lookup(selected_symbol)

        #Calculate cost
        total_cost = float(number_shares) * current_price["price"]
        price = current_price["price"]

        #Get current cash
        userCashList = db.execute("SELECT cash FROM users WHERE id = :user_id;", user_id=session["user_id"])
        current_cash = userCashList[0]["cash"]


        #Calculate new cash
        new_cash = current_cash + total_cost

        #Insert into transactions database
        transaction = db.execute("INSERT INTO transactions (user_id, symbol, price, amount, new_cash, type) VALUES (:user_id, :symbol, :price, :amount, :new_cash, :type)",
            user_id=session["user_id"], symbol=selected_symbol, price=price, amount=number_shares, new_cash=new_cash, type="Sale")

        #Update database with new cash
        cash_result = db.execute("UPDATE users SET cash = :new_cash WHERE id = :user_id;", new_cash = new_cash, user_id = session["user_id"])

        return render_template("sold.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
