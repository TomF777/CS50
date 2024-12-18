/*
Program that prompts the user for a credit card number and then reports (via printf) whether it is a valid American Express, MasterCard, or Visa card number, per the definitions of each’s format herein. 
The program’s last line of output should be AMEX\n or MASTERCARD\n or VISA\n or INVALID\n. 
For simplicity, you may assume that the user’s input will be entirely numeric (i.e., devoid of hyphens, as might be printed on an actual card) and that it won’t have leading zeroes.
*/


#include <cs50.h>
#include <stdio.h>

int check_card_length(long int card_number);
void check_card_type(long int card_number, int card_length);

int main(void)
{
    int digit_count = 0;

    // Prompt the user for card number
    long int number;
    do
    {
        number = get_long("Number: ");
    }
    while (number < 1);

    int length = check_card_length(number);
    check_card_type(number, length);
}

int check_card_length(long int card_number)
{
    int length = 1;
    while (card_number > 9)
    {
        length++;
        card_number /= 10;
    }
    return length;
}

void check_card_type(long int card_number, int card_length)
{
    int sum_even = 0, sum_odd = 0;
    int digit, first_digit, second_digit;

    // iterate through all digits
    for (int i = 0; i < card_length; i++)
    {
        digit = (int) (card_number % 10);
        // printf("dig: %i ", digit);

        // find 1st and 2nd digit for card type evaluation
        if (i == card_length - 2)
            second_digit = digit;

        if (i == card_length - 1)
            first_digit = digit;

        // detect odd/even digit;
        if (i % 2 == 1)
        // evaluate odd digits, i.e. starting from second's to last
        {
            digit = digit * 2;
            if (digit < 9)
            {
                sum_odd = sum_odd + digit;
            }
            else
            {
                sum_odd = sum_odd + (digit / 10) + (digit % 10);
            }
        }
        else
        // evaluate even digits, i.e. starting from last
        {
            sum_even = sum_even + digit;
        }

        // divide by 10 means moving into left of the card number
        card_number = card_number / 10;
    }

    // printf("\n 1st digit: %i  2nd digit: %i\n", first_digit, second_digit);
    // printf("\n sum odd: %i sum even: %i \n", sum_odd, sum_even);
    // printf(" sum total: %i ", sum_even + sum_odd);

    if ((sum_even + sum_odd) % 10 == 0)
    // valid credit card detected of eny type
    {
        if (first_digit == 4 && (card_length == 13 || card_length == 16))
        {
            printf("VISA\n");
        }
        else if (first_digit == 3 && (second_digit == 4 || second_digit == 7) && card_length == 15)
        {
            printf("AMEX\n");
        }
        else if ((first_digit * 10 + second_digit) >= 51 &&
                 (first_digit * 10 + second_digit) <= 55 && card_length == 16)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            // any other credit card but still valid card number
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
