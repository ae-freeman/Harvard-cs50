

//Include header files
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

string encryptedString ="";

//Define function to encrypt the text
string shiftResult(string keyWord, string plainText);

// declare int main with argc and argv
int main(int argc, string argv[])
{

// if there were not two arguments written in argc
if (argc != 2)
  {
  printf("Usage: ./vigenere keyword");
    return 1;
  }

//If they did enter the correct number

string keyWord = argv[1];


// prompt the user for a piece of plain text to encrypt, saving this to a string
string plainText = get_string("Plain text: ");


 // Print cipher text plus the result of each loop of the for loop
printf("Encrypted text: ");

//Call function to encrypt the text
string cipherText = shiftResult(plainText, keyWord);

//End main
}

//Definition of the function to encrypt the text
string shiftResult(string plainText, string keyWord){

int plainTextLength = strlen(plainText);
int keyWordLength = strlen(keyWord);


  //iterate through each character of the plain Text:
  for (int i = 0, keyWordIndex = 0; i < plainTextLength; i++)
  {
    if(isalpha(plainText[i])){


      //get the shift number from the keyword (making it all in lowercase)
      //Convert each char from keyword into alphabet index; if keyword[i] = d, then the shift     number is 3. 'd' - 97

    int keyWordCharLower = tolower(keyWord[keyWordIndex]);


    int shiftNumber = keyWordCharLower - 97;

       //Check if keyword char is lower case, upper case or punctuation
        if(islower(plainText[i]))

        //shift the plain text char by the ascii value of the shift char
        {
           int asciiPlainTextChar = plainText[i];

            int encryptedIntValue = (asciiPlainTextChar - 'a' + shiftNumber) % 26;


            char encryptedChar = encryptedIntValue + 'a';

          //Print the encrypted char
          printf("%c", encryptedChar);
        }


      else if (isupper(plainText[i]))
      {
      //shift the plain text char by the ascii value of the shift char

           int asciiPlainTextChar = plainText[i];

          int encryptedIntValue = (asciiPlainTextChar - 'A' + shiftNumber) % 26;


            char encryptedChar = encryptedIntValue + 'A';

          //Print the encrypted char
          printf("%c", encryptedChar);

      }

      //for other types of chars, print as is

         keyWordIndex++;
     if (keyWordIndex == keyWordLength){
         keyWordIndex = 0;
     }

    } else {
        printf("%c", plainText[i]);
    }



    //end for loop
    }

    printf("\n");
    return encryptedString;

        }
