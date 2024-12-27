/*
    The Collatz conjecture applies to positive integers and speculates
    that it is always possible to get "back to 1" if you
    follow these steps:
    - if n is 1 stop
    - otherwise, if n is even, repeat this process on n/2
    - otherwise, if n is odd, repeat this process on 3n + 1
*/

#include <cs50.h>
#include <stdio.h>

int collatz(int n);

int main(void)
{
    // get positive value for n
    int n;
    do
    {
        n = get_int("n: ");
    } while (n <= 0);

    printf("Collatz= %i\n", collatz(n));

}


int collatz(int n)
{
    // base case
    if (n == 1)
        return 0;
    // even numbers
    else if ((n % 2) == 0 )
        return 1 + collatz(n / 2);
    // odd numbers
    else
        return 1 + collatz(3 * n + 1);
}
