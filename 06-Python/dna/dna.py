import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("wrong usage")
        exit()
    database = sys.argv[1]
    sequence = sys.argv[2]

    # TODO: Read database file into a variable
    file = open(database, mode='r')
    csvFile = csv.reader(file)

    # TODO: Read DNA sequence file into a variable
    txtfile = open(sequence, "r")
    sequence = txtfile.read()

    # TODO: Find longest match of each STR in DNA sequence
    suspect_result = ["suspect"]

    for line in csvFile:
        if line[0] == "name":
            for i in range(1, len(line)):
                suspect_result.append(longest_match(sequence, line[i]))
            break

    # TODO: Check database for matching profiles
    for line in csvFile:
        if line[0] != "name":
            for i in range(1, len(line), 1):
                if int(suspect_result[i]) == int(line[i]):
                    if i == len(line) - 1:
                        print(f"{line[0]}")
                        exit()
                    else:
                        continue
                else:
                    break

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
