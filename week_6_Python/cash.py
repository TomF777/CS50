""" 
Suppose that a cashier owes a customer some change and in that cashier’s drawer are quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢). 
The problem to be solved is to decide which coins and how many of each to hand to the customer. 
Think of a “greedy” cashier as one who wants to take the biggest bite out of this problem as possible with each coin they take out of the drawer. 
For instance, if some customer is owed 0.41$, the biggest first (i.e., best immediate, or local) bite that can be taken is 0.25$. 
(That bite is “best” inasmuch as it gets us closer to 0$ faster than any other coin would.) 
Note that a bite of this size would whittle what was a 0.41$ problem down to a 0.16$ problem, since 0.41 - 0.25 = 0.16. 
That is, the remainder is a similar but smaller problem. 
Needless to say, another 0.25$ bite would be too big (assuming the cashier prefers not to lose money), and so our greedy cashier would move on to a bite of size 0.10$, 
leaving him or her with a 0.06$ problem. 
At that point, greed calls for one 0.05$ bite followed by one 0.01$ bite, at which point the problem is solved. 
The customer receives one quarter, one dime, one nickel, and one penny: four coins in total

The user will input his change in dollars (e.g. 0.50) not in cents.
"""


import cs50


def main():

    # Prompt the user for change owed, in dollars
    dollars = -1.0
    while dollars < 0:
        dollars = cs50.get_float("Change owed: ")

    # convert float to int and dollars to cents calculation
    dollars = int(dollars * 100)

    # Calculate how many quarters you should give customer
    quarters = calculate_quarters(dollars)
    # Subtract the value of those quarters from cents
    dollars = dollars - (quarters * 25)

    # Calculate how many dimes you should give customer
    dimes = calculate_dimes(dollars)
    # Subtract the value of those dimes from remaining cents
    dollars = dollars - (dimes * 10)

    # Calculate how many nickels you should give customer
    nickels = calculate_nickels(dollars)
    # Subtract the value of those nickels from remaining cents
    dollars = dollars - (nickels * 5)

    # Calculate how many pennies you should give customer
    pennies = calculate_pennies(dollars)
    # Subtract the value of those pennies from remaining cents
    dollars = dollars - (pennies * 1)

    # Sum the number of quarters, dimes, nickels, and pennies used
    sum = quarters + dimes + nickels + pennies
    # Print that sum
    print(f"{sum}")


# *********************
# function declaration
# *********************

def calculate_quarters(cents):

    # Calculate how many quarters you should give customer
    quarters = 0
    while cents >= 25:
        quarters += 1
        cents -= 25

    return quarters


def calculate_dimes(cents):

    # Calculate how many dimes you should give customer
    dimes = 0
    while cents >= 10:
        dimes += 1
        cents -= 10

    return dimes


def calculate_nickels(cents):

    # Calculate how many nickels you should give customer
    nickels = 0
    while cents >= 5:
        nickels += 1
        cents -= 5

    return nickels


def calculate_pennies(cents):

    # Calculate how many pennies you should give customer
    pennies = 0
    while cents >= 1:
        pennies += 1
        cents -= 1

    return pennies


# main program
if __name__ == "__main__":
    main()
