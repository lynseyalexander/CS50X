#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Add function protoypes
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int colemanLiauIndex(string text);

int main(void)
{
    // ask user to input text
    string text = get_string("Text: ");

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    int grade = colemanLiauIndex(text);

    return 0;

}

// Create count_letters function
int count_letters(string text)
{

    // count the number of alphabetical letters within the text
    // take a string of text and return an int - the number of letters
    int count;
    int letters = 0;

    for (count = 0; count < strlen(text); count++)
    {
        if (isalpha(text[count]))
        {
            letters++;
        }
    }

    return letters;
}

// Create count_words function
int count_words(string text)
{
    // count the number of words within the text
    // return the number of words as an int
    int count_w;
    int words = 1;

    for (count_w = 0; count_w < strlen(text); count_w++)
    {
        if (text[count_w] == ' ')
        {
            words++;
        }
    }

    return words;
}

// Create count_sentences function
int count_sentences(string text)
{
    // count the number of sentences within the text
    // return number of sentences as an int.
    int count_s;
    int sentences = 0;

    for (count_s = 0; count_s < strlen(text); count_s++)
    {
        if (text[count_s] == '.' || text[count_s] == '!' || text[count_s] == '?')
        {
            sentences++;
        }
    }

    return sentences;
}

int colemanLiauIndex(string text)
{
    // import variables from other functions
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Using number of letters, words and sentences via Coleman-Liau Index calculate reading grade.
    // set a float variable to calculate the average words and sentences
    // float needs parenthesis to force the complier to treat the result as a float
    float averageLetters = (float) letters / words * 100;
    float averageSentences = (float) sentences / words * 100;

    // use the coleman liau index to calculate the reading grade.
    float colemanLiau = (0.0588 * averageLetters) - (0.296 * averageSentences) - 15.8;

    // round to the nearest int and return grade
    int grade = round(colemanLiau);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }

    return 0;
}