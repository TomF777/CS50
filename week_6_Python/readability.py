"""
Program that calculates the approximate grade level needed to comprehend some text. 
The program should print as output “Grade X” where “X” is the grade level computed, rounded to the nearest integer. 
If the grade level is 16 or higher (equivalent to or greater than a senior undergraduate reading level), 
the program should output “Grade 16+” instead of giving the exact index number. 
If the grade level is less than 1, the program should output “Before Grade 1”.

Background:
So what sorts of traits are characteristic of higher reading levels? 
Longer words probably correlate with higher reading levels. Likewise, longer sentences probably correlate with higher reading levels, too.
A number of “readability tests” have been developed over the years that define formulas for computing the reading level of a text. 
One such readability test is the Coleman-Liau index. 
The Coleman-Liau index of a text is designed to output that (U.S.) grade level that is needed to understand some text. The formula is:

index = 0.0588 * L - 0.296 * S - 15.8

where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.
"""

import cs50


def main():

    text = cs50.get_string("Text: ")

    # calculate number of letters, words & sentences in text
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # compute the Coleman-Liau index
    index = round(0.0588 * (float(letters) / float(words) * 100.0) - 0.296 *
                  (float(sentences) / float(words) * 100.0) - 15.8, 0)

    if index < 1:
        print(f"Before Grade 1")
    elif index > 16:
        print(f"Grade 16+")
    else:
        print(f"Grade {index}")

# *********************
# functions declaration
# *********************
def count_letters(text):
    #  Return number of letters in text

    letters = 0
    [letters := letters + 1 for char in text if char.isalpha()]

    return letters


def count_words(text):
    # Return number of words in text

    # calculate number of spaces in a text
    spaces = 0
    [spaces := spaces + 1 for char in text if char.isspace()]

    return spaces + 1


def count_sentences(text):
    # Return the number of sentences in text

    special_char = ['?', '!', '.']
    sentences = 0
    for idx in range(len(text)):
        sentences = sentences + 1 if text[idx] in special_char else sentences

    return sentences


# call main program
if __name__ == "__main__":
    main()
