import csv
import sys
from sys import argv


def main():

    # Check for command-line usage
    # 1st argument must be name of csv file, 2nd argument must be text file
    if len(argv) != 3:
        print(f"Wrong number of command-line arguments")
        sys.exit(1)

    # Read database file into a variable
    database_file = argv[1]
    with open(database_file) as file:
        reader = csv.DictReader(file)

        # convert csv file into list object
        database = list(reader)

    # Read DNA sequence file into a variable
    dna_seq_file = argv[2]
    with open(dna_seq_file) as file:
        dna_seq = file.read()

    # Find longest match of each STR in DNA sequence
    str_longest_match = {}
    for str in list(database[0].keys())[1:]:
        str_longest_match[str] = longest_match(dna_seq, str)

    # Check database for matching profiles
    # iterate all rows of csv (except of header) i.e. iterate all persons
    for row in range(len(database)):

        # number of matches for each str
        matches = 0

        # person name
        person_name = database[row]["name"]

        # iterate all columns of csv i.e. find longest run for each STR of each person
        for col in str_longest_match:
            if int(str_longest_match[col]) == int(database[row][col]):
                matches += 1

        # match for each STR for given person
        if matches == len(str_longest_match.keys()):
            print(f"{person_name}")
            sys.exit(1)

    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
