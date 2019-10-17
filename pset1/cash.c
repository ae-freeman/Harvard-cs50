//Abstractions and scope
#include <cs50.h>
#include <stdio.h>
#include <math.h>

float getChangeOwed(string prompt);
int calculateCoinCount(int cents);



int main(void)
{

   float totalChange = getChangeOwed("Change owed: ");

    int cents = round(totalChange * 100);

    int coinCount = calculateCoinCount(cents);
    printf("The total number of coins is: %i\n", coinCount);


}

 // Prompt user for a positive floating point
float getChangeOwed (string prompt)
{
    float change;
    do {
        change = get_float("%s", prompt);
    }
    while (change < 0);
    return change;
}


  // Calculate number of coins
int calculateCoinCount (int p_totalCents) {
    int leftOverCents = p_totalCents;
    int coinCount;



    coinCount = floor(leftOverCents/25);
       leftOverCents = leftOverCents%25;


    if (leftOverCents == 0) {
        return coinCount;
    }

     coinCount = floor(leftOverCents/10) + coinCount;
       leftOverCents = leftOverCents%10;

    if (leftOverCents == 0) {
        return coinCount;
    }

     coinCount = floor(leftOverCents/5) + coinCount;
       leftOverCents = leftOverCents%5;

    if (leftOverCents == 0) {
        return coinCount;
    }

     coinCount = floor(leftOverCents/1) + coinCount;
       leftOverCents = leftOverCents%1;


        return coinCount;


  }
