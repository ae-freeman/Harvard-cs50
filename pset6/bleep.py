import sys
from cs50 import get_string
from sys import argv


def main():

#1. Check there are two command line arguments
    if len(argv) != 2:
    #if not, use sys.exit(1)
        print("Invalid arguments")
        sys.exit(1)
#2. Save the second argument into a variable (does this have to be of a file type?)
#3. Open file
#Define set
    words =  set(open(sys.argv[1]).read().split())

#4. already done!

#5. Get string from user and store into a variable
    userString = get_string("What message would you like to censor? ")

#6. Split the string, separation is " " (this will return as a list)
    eachWord = (userString.split())

#7. Start a for loop, for each item in the userString
    for bleepWord in eachWord:
        lower = bleepWord.lower()
        if lower in words:
            bleepWord = '*' * len(bleepWord)
            print(bleepWord, end=" ")

        else:
            print(bleepWord, end=" ")

    print()

#10. Close file



if __name__ == "__main__":
    main()
