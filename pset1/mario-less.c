// Abstraction and scope

#include <cs50.h>
#include <stdio.h>

int get_correct_int(string prompt);
int n;

int main(void)
{
    int maxChars = get_correct_int("Number between 1 and 8: ");
    for (int rowNumber = 0; rowNumber < maxChars; rowNumber++) {
        int hashCount = rowNumber + 1;
        int maxSpaceCount = maxChars - hashCount;
         for (int spaceCount = 0; spaceCount < maxSpaceCount; spaceCount++){
             printf(" ");
         }

        for (int j = 0; j < hashCount; j++) {
            printf("#");
        }
        printf("\n");
    }
}

// Prompt user for number between 1 and 8
int get_correct_int(string prompt)
{

    do {
        n = get_int("%s", prompt);
    }
    while (n < 1 || n > 8);
    return n;
}
