import sys
from sys import argv
from cs50 import get_string

if len(argv) != 2:
    print("Invalid input")
    sys.exit(1)

k = int(argv[1])

plainText = get_string("Plain text: ")
print("ciphertext: ", end="")

#find length of plaintext
lengthPlainText = len(plainText)

#iterate through plaintext letters
for i in range(lengthPlainText):

    #check if lowercase
    if ord(plainText[i]) >= (ord('a')) and ord(plainText[i]) <= (ord('z')):
        #shift letter using k and % 26
        cipher = ((((ord(plainText[i]) - (ord('a'))) + k) % 26) + (ord('a')))
        print(chr(cipher),end="")

    #check if upper case
    elif ord(plainText[i]) >= (ord('A')) and ord(plainText[i]) <= (ord('Z')):
        #shift letter using k and % 26
        cipher = ((((ord(plainText[i]) - (ord('A'))) + k) % 26) + (ord('A')))
        print(chr(cipher), end="")
    #else, print the character
    else:
        print(plainText[i], end="")

print()
