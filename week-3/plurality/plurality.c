#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates //constant
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

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
// vote function accepts a single argument - string name.
bool vote(string name)
{
    // create variable to hold number of candidate names
    int voterNameCount;

    // count and loop through the number of candidate names
    for (voterNameCount = 0; voterNameCount < candidate_count; voterNameCount++)
    {
        // create variable to hold the candidates name
        string candidate_name = candidates[voterNameCount].name;

        // compare name string variable with candidate_name string variable
        // if they match then add a vote to the candidates total votes variable.
        if (strcmp(candidate_name, name) == 0)
        {
            candidates[voterNameCount].votes++;
            return true;
        }

    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // set variables
    int voteCount;
    int winningVote = 0;

    // count the votes cast for each candidate by looping through the array
    for (voteCount = 0; voteCount < candidate_count; voteCount++)
    {
        // set a variable to hold the votes per candidate
        int candidate_votes = candidates[voteCount].votes;

        // if the candidate votes are more than the value of the winning
        // vote variable then set it as the value of winningVote
        if (candidate_votes > winningVote)
        {
            winningVote = candidate_votes;
        }

    }

    // loop through the votes again to find those of equal value
    for (voteCount = 0; voteCount < candidate_count; voteCount++)
    {
        // set variables to hold the votes and name from the struct array
        int candidate_votes = candidates[voteCount].votes;
        string candidate_name = candidates[voteCount].name;

        // if an candidates have an equal amount of votes set in the
        // winningVote variable then print the candidates name followed by \n
        if (candidate_votes == winningVote)
        {
            printf("%s\n", candidate_name);
        }
    }

    return;
}