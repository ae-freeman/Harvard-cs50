from cs50 import get_int

while True:
    #get number from user
    n = get_int("Height: ")
    #check if valid
    if n > 0 and n < 9:
        break



#initialise counter variables
hashCounter = 1;
spaceCounter = n-1;

#start nested for loops to print staircase
for i in range(n):
    for k in range(spaceCounter):
        print(" ", end="")



    for j in range(hashCounter):
        print("#", end="")

    hashCounter += 1
    spaceCounter -= 1


    print()
