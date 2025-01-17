"""Implement a program in C that recreates that pyramid, using hashes (#) for bricks, as in the below:
       #
      ##
     ###
    ####
   #####
  ######
 #######
########

But prompt the user for an int for the pyramid’s actual height, so that the program can also output shorter pyramids like the below:
  #
 ##
###

Re-prompt the user, again and again as needed, if their input is not greater than 0 or not an int altogether.
"""

import cs50


def main():
    height = 0

    # get user input for pyramid height
    while height < 1 or height > 8:
        height = cs50.get_int("Height: ")

    # create pyramid with loop
    for row in range(1, height + 1):
        print_row(height - row, row)


def print_row(spaces, bricks):

    # print spaces
    for _ in range(spaces):
        print(" ", end="")

    # print bricks
    for _ in range(bricks):
        print("#", end="")
    print()


# main program
if __name__ == "__main__":
    main()
