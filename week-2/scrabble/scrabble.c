#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    // if score1 is higher than score2
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    // if score1 and score2 are equal
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
    // if score1 is less than score2
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        return 0;
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    // set playerScore variable
    int playerScore = 0;

    // to align letters with the POINTS[] array we must minus the ASCII character value from the index
    // for uppercase letters we must minus the value of 65 or char 'A' (which is ASCII value 65)
    // for lowercase letters we must minus the value of 97 or char 'a' (which is ASCII value of 97)
    // isupper - if letter is between ASCII 65 and 90
    // islower - if letter is between ASCII 97 and 122
    for (int letter = 0; letter <= strlen(word); letter++)
    {
        if (isupper(word[letter]))
        {
            playerScore += POINTS[word[letter] - 65];
        }
        else if (islower(word[letter]))
        {
            playerScore += POINTS[word[letter] - 97];
        }
    }
    return playerScore;
}
