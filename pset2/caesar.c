#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, string argv[])
{

if (argc != 2)
    {
      //If there are an incorrect number of arguments:
         printf("Usage: ./caesar key\n");
         return 1;

    }
    
    int k = atoi(argv[1]); //Convert into an integer

    string plainText = get_string("plaintext: ");
    printf("ciphertext: "); //title for the cipher text

    int n = strlen(plainText);
    //iterate through text letter by letter
    for (int i = 0; i < n; i++) {

       if (plainText[i] >= 'a' && plainText[i] <= 'z')
       {
           //Check if is lowercase
           printf("%c", (((plainText[i] - 'a') + k) % 26) + 'a');// print out lowercase with key
       } else if (plainText[i] >= 'A' && plainText[i] <= 'Z')

           {
               printf("%c", (((plainText[i] - 'A') + k) % 26) + 'A');
           } else

           {
               printf("%c", plainText[i]);
           }
       }
    printf("\n");
    return 0;
}

   int n = strlen(argv[1]);

    //iterate through text letter by letter
    for (int i = 0; i < n; i++)
    {
        printf("%c", isalpha(i));
    }

    string plainText = get_string("plaintext: ");
    printf("ciphertext: "); //title for the cipher text

    int length = strlen(plainText);
    //iterate through text letter by letter
    for (int i = 0; i < length; i++) {

       if (plainText[i] >= 'a' && plainText[i] <= 'z')
       {
           //Check if is lowercase
           printf("%c", (((plainText[i] - 'a') + k) % 26) + 'a');// print out lowercase with key
       } else if (plainText[i] >= 'A' && plainText[i] <= 'Z')

           {
               printf("%c", (((plainText[i] - 'A') + k) % 26) + 'A');
           } else

           {
               printf("%c", plainText[i]);
           }
       }
    printf("\n");
    return 0;
}
