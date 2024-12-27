/*
Simplest way to hold an election, is via a method commonly known as the “plurality vote” (also known as “first-past-the-post” or “winner take all”). 
In the plurality vote, every voter gets to vote for one candidate. 
At the end of the election, whichever candidate has the greatest number of votes is declared the winner of the election.

The program shall be called with command-line arguments which are candidate's names e.g. ./plurality Alce Bob Charlie
It asks for the voter number.
Next the program lets every voter type in a vote for each candidate.
Finally , the winner(s) with the most votes should be printed out.
*/
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Iterate over each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if candidate's name matches given name
        if (strcmp(candidates[i].name, name) == 0)
        // If yes, increment candidate's votes and return true
        {
            candidates[i].votes++;
            return true;
        }
    }

    // If no match, return false
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int max_votes = 0;
    // Find the maximum number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes)
            max_votes = candidates[i].votes;
    }

    // Print the candidate (or candidates) with maximum votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}
