#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// define function prototypes
bool isKeyValid(string key);
string substitute(string plaintext, string key);

int main(int argc, string argv[])
{

    // Accept a single command line argument - the key.
    // if executed without any command line arguments or with more than one
    // print an error message and return 1.
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // if key doesn't contain 26 characters then display an error and return 1.
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }

    // create key variable from command line command input
    string key = argv[1];

    // call function isKeyValid
    isKeyValid(key);

    // Prompt user for string called plaintext
    string plaintext = get_string("plaintext: ");

    // call function substitute
    substitute(plaintext, key);

    return 0;
}

bool isKeyValid(string key)
{
    // set variable to check chars in key
    int keyCharCount;
    string duplicateKey = key;

    for (keyCharCount = 0; keyCharCount < strlen(key); keyCharCount++)
    {
        // if the key contains characters that are not alphabetical
        // print an error and return 1
        if (!isalpha(key[keyCharCount]))
        {
            printf("All characters in key must be alphabetic.\n");
            exit(1);
        }
        // if the key contains duplicate characters
        // set all chars to uppercase to be able to compare upper and lower duplicated chars.
        // print an error and return 1
        if (strchr(key + keyCharCount + 1, toupper(duplicateKey[keyCharCount])))
        {
            printf("Must not contain duplicate characters. \n");
            exit(1);
        }
    }

    return 0;
}

string substitute(string plaintext, string key)
{
    // print "ciphertext"
    printf("ciphertext: ");

    // create variable to hold ciphertext chars
    int cipherText;

    // followed by the plaintext's corresponding ciphertext

    // set cipherText to zero. loop through plaintext variable.
    for (cipherText = 0; cipherText < strlen(plaintext); cipherText++)
    {
        // check that characters are alphabetical
        if (isalpha(plaintext[cipherText]))
        {
            // if lowercase chars then minus the ASCII value of a (97)
            if (islower(plaintext[cipherText]))
            {
                int cipher = plaintext[cipherText] - 97;
                printf("%c", tolower(key[cipher]));

            }
            // if uppercase chars then minus the ASCII value of A (65)
            else if (isupper(plaintext[cipherText]))
            {
                int cipher = plaintext[cipherText] - 65;
                printf("%c", toupper(key[cipher]));
            }
        }
        else
        {
            // If character is punctuation such as '!' or '?', print this unchanged.
            printf("%c", plaintext[cipherText]);
        }

    }
    // print a new line
    printf("\n");

    // exit by returning 0 from main.
    return 0;
}