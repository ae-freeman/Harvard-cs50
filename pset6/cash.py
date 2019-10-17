from cs50 import get_float
import math

def main():

    while True:
        #get number from user
        changeOwed = get_float("Change owed: ")
        #check if valid
        if changeOwed > 0:
            break

    totalCents = changeOwed * 100
    finalResult = calculateCoinCount(totalCents)
    print("The total number of coins is: ", finalResult)

def calculateCoinCount(totalCents):
    leftOverCents = totalCents
    coinCount = 0

    coinCount = math.floor(leftOverCents / 25)
    leftOverCents = leftOverCents % 25

    if leftOverCents == 0:
        return coinCount


    coinCount = math.floor(leftOverCents / 10) + coinCount
    leftOverCents = leftOverCents % 10

    if leftOverCents == 0:
        return coinCount


    coinCount = math.floor(leftOverCents / 5) + coinCount
    leftOverCents = leftOverCents % 5

    if leftOverCents == 0:
        return coinCount


    coinCount += leftOverCents


    return coinCount


if __name__ == "__main__":
    main()
