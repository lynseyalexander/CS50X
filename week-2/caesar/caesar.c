#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

// add function prototypes
bool only_digits(string key);
string caesarCipher(string plaintext, int intKey);

int main(int argc, string argv[])
{
    // arcg counts the command line arguments.
    // if agrc is supplied with less than or more than 2 args (program name and key) display an error
    // Return 1 (end program) else Return 0.
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // set variables
    string key = argv[1];

    // call the only_digits function
    only_digits(key);

    // convert argv[1] (key) to an int
    int keyToInt = atoi(key);

    // ask user for plaintext input using get_string
    string plaintext = get_string("plaintext:  ");

    // call the caesarCipher funtcion
    // use (char) to implicity cast plaintext variable as char
    caesarCipher(plaintext, keyToInt);

    return 0;
}

// create a Function called only_digits
bool only_digits(string key)
{
    int count;

    // take a string as an argument and return true if that string only contains digits
    // else return false.
    for (count = 0; count < strlen(key); count++)
    {
        if (!isdigit(key[count]))
        {
            exit(1);
        }
    }

    return 0;
}

// create a function called caesarCipher
string caesarCipher(string plaintext, int intKey)
{
    printf("ciphertext: ");

    int cipherText;

    // set cipherText to zero. loop through plaintext variable.
    for (cipherText = 0; cipherText < strlen(plaintext); cipherText++)
    {

        // if a character is alphabetical
        if (isalpha(plaintext[cipherText]))
        {
            // if characters are lowercase
            if (islower(plaintext[cipherText]))
            {
                // calculate caesar cipher. 97 is used as it is the ASCII value of 'a'.
                int cipher = ((plaintext[cipherText] - 97) + intKey) % 26 + 97;
                printf("%c", cipher);
            }
            // if characters are uppercase
            else if (isupper(plaintext[cipherText]))
            {
                // calculate caesar cipher. 65 is used as it is the ACSII value of 'A'.
                int cipher = ((plaintext[cipherText] - 65) + intKey) % 26 + 65;
                printf("%c", cipher);
            }

        }
        else
        {
            // If character is punctuation such as '!' or '?', print this unchanged.
            printf("%c", plaintext[cipherText]);
        }

    }
    printf("\n");

    return 0;
}