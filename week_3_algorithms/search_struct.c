/*
Search algorithm on struct data
*/
#include <cs50.h>
#include <stdio.h>

typedef struct {
    string name;
    int votes;
} candidate;

int main(void)
{
    const int num_candidates = 3;
    candidate candidates[num_candidates];

    candidates[0].name = "Bill";
    candidates[0].votes = 23;

    candidates[1].name = "John";
    candidates[1].votes = 56;

    candidates[2].name = "Mary";
    candidates[2].votes = 33;

    // find highest number of votes
    int highest_votes = 0;
    int highest_index = 0;
    for (int i = 0; i < num_candidates; i++)
    {
        if (candidates[i].votes > highest_votes)
        {
            highest_votes = candidates[i].votes;
            highest_index = i;
        }
    }
    printf("%i\n", highest_votes);

    // print name of candidate with highest number of votes
    printf("Candidate :%s\n", candidates[highest_index].name);

}
