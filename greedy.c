/*
    My first program to use a Greedy algorithm, designed to be used by a cashier.
    In the terminal, the user is asked how much change is owed.
    The program calculates the number of notes/coins to give as change,
    using a greedy approach to minimise change.
    
    Written by Joshua Scott for Harvard's 'CS50' online course:
    http://online-learning.harvard.edu/course/cs50-introduction-computer-science
    GitHub: https://github.com/jscott313
*/

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int dollars = 0;
    int quarters = 0;
    int dimes = 0;
    int nickels = 0;
    int pennies = 0;

    float amountOwed;

    // Get amount owed in dollars, e.g. 1.23
    do
    {
        printf("How much changed is owed?\n");
        amountOwed = GetFloat();
    }
    while (amountOwed < 0.00);

    // Convert amount owed to cents
    int centsOwed = round(amountOwed*100);
    
    // Greedily use as many of each denomination as possible, 
    // until the remaining centsOwed is 0

    while (centsOwed >= 100)
    {
        centsOwed -= 100;
        dollars++;
    }

    while (centsOwed >= 25)
    {
        centsOwed -= 25;
        quarters++;
    }
    
    while (centsOwed >= 10)
    {
        centsOwed -= 10;
        dimes++;
    }
    
    while (centsOwed >= 5)
    {
        centsOwed -= 5;
        nickels++;
    }
    
    while (centsOwed > 0)
    {
        centsOwed -= 1;
        pennies++;
    }
    
    // Display how many of each denomination is owed, one per line
    printf( "Dollars: %i\n",    dollars     +
            "Quarters: %i\n",   quarters    +
            "Dimes: %i\n",      dimes       +
            "Nickels: %i\n",    nickels     +
            "Pennies: %i\n",    pennies     );
}
