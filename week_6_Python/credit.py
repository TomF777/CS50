"""
Program that prompts the user for a credit card number and then reports whether it is a valid 
American Express, MasterCard, or Visa card number, per the definitions of each’s format herein. 
The program’s last line of output should be AMEX\n or MASTERCARD\n or VISA\n or INVALID\n. 
For simplicity, you may assume that the user’s input will be entirely numeric 
(i.e., devoid of hyphens, as might be printed on an actual card) and that it won’t have leading zeroes.
"""

import cs50

def main():

    # Prompt the user for card number
    number = 0
    while number < 1:
        number = cs50.get_int("Number: ")


    length = check_card_length(number)
    check_card_type(number, length)


def check_card_length(card_number):

    # calculate card length
    return len(str(card_number))


def check_card_type(card_number, card_length):
    # define card type

    first_digit = int(str(card_number)[0])
    second_digit = int(str(card_number)[1])

    # convert number to list and reverse its order
    card_num_odd = list(map(int, str(card_number)))
    card_num_odd.reverse()

    sum_odd = 0
    sum_even = 0

    # evaluate odd digits, i.e. starting from second's to last, every second digit
    for digit in card_num_odd[1::2]:
        digit *= 2
        if digit < 9:
            sum_odd += digit
        else:
            sum_odd += int(digit / 10) + int(digit % 10)

    # evaluate even digits, i.e. starting from last, every second digit
    for digit in card_num_odd[0::2]:
        sum_even += digit

    sum_total = sum_odd + sum_even

    # valid credit card detected of any type
    if sum_total % 10 == 0:
        if first_digit == 4 and (card_length == 13 or card_length == 16):
            print("VISA")

        elif first_digit == 3 and (second_digit == 4 or second_digit == 7) and card_length == 15:
            print("AMEX")

        elif ((first_digit * 10 + second_digit) >= 51) and ((first_digit * 10 + second_digit) <= 55) and card_length == 16:
            print("MASTERCARD")

        else:
            # any other credit card but still valid card number
            print("INVALID")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()

