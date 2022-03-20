#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates // constant
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    // first argument is zero - this is the program "./runoff",
    // argc - 1 gives us the end of that argc array in this case the "candidate names list".
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        // this selects the second argument as the first argument is the program itself "./runoff"
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // create variable
    int validcandidateName = 0;

    // loop through every candidate name to ensure that it is valid
    for (validcandidateName = 0; validcandidateName < candidate_count; validcandidateName++)
    {
        // create variable to hold candidates name
        string candidateName = candidates[validcandidateName].name;

        // find out if the name entered matches the candiates name.
        // strcmp() uses == 0 to indicate if the name is equal.
        if (strcmp(candidateName, name) == 0)
        {
            // populate the voters preference
            // voter holds the voters ID | rank holds the candidates ID
            // if the preference is sucessfully recored - return true;
            preferences[voter][rank] = validcandidateName;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // ID of the current voter
    int currentVoter;

    // loop through each voter
    for (currentVoter = 0; currentVoter < voter_count; currentVoter++)
    {
        // the current voters 1st, 2nd, 3rd etc... candidate choice.
        int currentvotersRank;

        // loop through each candidate chosen
        for (currentvotersRank = 0; currentvotersRank < candidate_count; currentvotersRank++)
        {

            // store voters ID and Candidates ID depending on their rank (1st choice, 2nd choice etc..)
            // bool variable to hold false or true depending on candidate elimination status
            int chosenCandidate = preferences[currentVoter][currentvotersRank];
            bool eliminatedCandidate = candidates[chosenCandidate].eliminated;

            // check if the candidate has been eliminated - if not continue
            if (!eliminatedCandidate)
            {
                // increment candidate vote by 1
                // end the loop using break;
                candidates[chosenCandidate].votes++;
                break;
            }

        }
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // set variable
    int candidateVotes;

    // divide the candidates total votes by 2
    int winningPercent = voter_count / 2;

    // loop through the votes per candidate
    for (candidateVotes = 0; candidateVotes  < candidate_count; candidateVotes++)
    {
        // hold the total number of votes for the candidate
        int candidatetotalVotes = candidates[candidateVotes].votes;

        // if vote count is more than 50% of total votes then return true and print candidates name.
        if (candidatetotalVotes > winningPercent)
        {
            printf("%s\n", candidates[candidateVotes].name);
            return true;
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // set variable
    int totalvoteCount;

    // get the first voters candidate
    int minVotes = candidates[0].votes;

    // loop through the candidate(s)
    for (totalvoteCount = 0; totalvoteCount < candidate_count; totalvoteCount++)
    {
        // create variable to hold the candidates eliminated status
        bool eliminated = candidates[totalvoteCount].eliminated;

        // hold the total votes the candidate has
        int votes = candidates[totalvoteCount].votes;

        // if the candidate has not been eliminated and has
        // less than the current minimum of votes, set minVotes.
        if (!eliminated && minVotes < votes)
        {
            minVotes = candidates[totalvoteCount].votes;
        }

    }

    // return minVotes to the program -- important!
    return minVotes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int candidatesVotes;

    // loop through candidates
    for (candidatesVotes = 0; candidatesVotes < candidate_count; candidatesVotes++)
    {
        // set variable to hold candidate status - eliminated - false | true
        bool isEliminated = candidates[candidatesVotes].eliminated;

        // if candidate has been eliminated and the votes are not equal to min
        // return false
        if (!isEliminated && candidates[candidatesVotes].votes != min)
        {
            return false;
        }
    }

    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{

    int voteCount;

    // loop though candidate and count votes
    for (voteCount = 0; voteCount < candidate_count; voteCount++)
    {
        // if the votes are above the minimum threshold
        // change eliminated variable to true
        if (candidates[voteCount].votes == min)
        {
            candidates[voteCount].eliminated = true;
        }
    }

    return;
}