/* 
Suppose that a cashier owes a customer some change and in that cashier’s drawer are quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢). 
The problem to be solved is to decide which coins and how many of each to hand to the customer. 
Think of a “greedy” cashier as one who wants to take the biggest bite out of this problem as possible with each coin they take out of the drawer. 
For instance, if some customer is owed 41¢, the biggest first (i.e., best immediate, or local) bite that can be taken is 25¢. 
(That bite is “best” inasmuch as it gets us closer to 0¢ faster than any other coin would.) 
Note that a bite of this size would whittle what was a 41¢ problem down to a 16¢ problem, since 41 - 25 = 16. That is, the remainder is a similar but smaller problem. 
Needless to say, another 25¢ bite would be too big (assuming the cashier prefers not to lose money), and so our greedy cashier would move on to a bite of size 10¢, 
leaving him or her with a 6¢ problem. 
At that point, greed calls for one 5¢ bite followed by one 1¢ bite, at which point the problem is solved. The customer receives one quarter, one dime, one nickel, and one penny: four coins in total
*/

#include <cs50.h>
#include <stdio.h>

int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Prompt the user for change owed, in cents
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    // Calculate how many quarters you should give customer
    int quarters = calculate_quarters(cents);
    // Subtract the value of those quarters from cents
    cents = cents - (quarters * 25);

    // Calculate how many dimes you should give customer
    int dimes = calculate_dimes(cents);
    // Subtract the value of those dimes from remaining cents
    cents = cents - (dimes * 10);

    // Calculate how many nickels you should give customer
    int nickels = calculate_nickels(cents);
    // Subtract the value of those nickels from remaining cents
    cents = cents - (nickels * 5);

    // Calculate how many pennies you should give customer
    int pennies = calculate_pennies(cents);
    // Subtract the value of those pennies from remaining cents
    cents = cents - (pennies * 1);

    // Sum the number of quarters, dimes, nickels, and pennies used
    int sum = quarters + dimes + nickels + pennies;
    // Print that sum
    printf("%i\n", sum);
    printf("quarters: %i, dimes: %i, nickels: %i, pennies: %i", quarters, dimes, nickels, pennies);
}

// *********************
// function declaration
// *********************
int calculate_quarters(int cents)
{
    // Calculate how many quarters you should give customer
    int quarters = 0;
    while (cents >= 25)
    {
        quarters++;
        cents = cents - 25;
    }
    return quarters;
}

int calculate_dimes(int cents)
{
    // Calculate how many dimes you should give customer
    int dimes = 0;
    while (cents >= 10)
    {
        dimes++;
        cents = cents - 10;
    }
    return dimes;
}

int calculate_nickels(int cents)
{
    // Calculate how many nickels you should give customer
    int nickels = 0;
    while (cents >= 5)
    {
        nickels++;
        cents = cents - 5;
    }
    return nickels;
}

int calculate_pennies(int cents)
{
    // Calculate how many pennies you should give customer
    int pennies = 0;
    while (cents >= 1)
    {
        pennies++;
        cents = cents - 1;
    }
    return pennies;
}
