"""Implement a program in C that recreates that pyramid, using hashes (#) for bricks, as in the below:

   #  #
  ##  ##
 ###  ###
####  ####

And let’s allow the user to decide just how tall the pyramids should be by first prompting them for a positive int between, say, 1 and 8, inclusive.
"""

import cs50

def main():
    height = 0

    # get user input for pyramid height
    while height < 1 or height > 8:
        height = cs50.get_int("Height: ")

    # create pyramid with loop
    for row in range(1, height + 1):
        print_row_right(height - row, row)
        print("  ", end="")
        print_row_left(row)
        print()


# **********************
# function declarations
# **********************
def print_row_right(spaces, bricks):
    # print right assigned rows

    for _ in range(spaces):
        print(" ", end="")
    for _ in range(bricks):
        print("#", end="")


def print_row_left(length):
    # print left assigned row

    for _ in range(length):
        print("#", end="")


# main program
if __name__ == "__main__":
    main()
