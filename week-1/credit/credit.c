#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // create variables
    long number;
    int digit;
    int length = 0;
    int position = 0;
    int sum; // total sum of all digits added together
    int parity = (length - 2) % 2; // even or odd
    long last_digit;
    int final_sum; // Adding the sum of digits not multiplied by 2.
    long first_digit;
    long first_two_digits;
    bool valid;

    // Ask user to input credit card number
    do
    {
        number = get_long("Number: ");
    }
    while (number <= 0);

    // set variables to equal number
    first_two_digits = number;
    first_digit = number;
    last_digit = number;

    // Get the first digit
    while (first_digit >= 10)
    {
        first_digit /= 10;
    }

    // Get the last digit
    while (last_digit >= 10)
    {
        last_digit = last_digit % 10;
    }

    // Get the first two digits
    while (first_two_digits > 100)
    {
        first_two_digits /= 10;
    }

    // Luhn algorithm for checksum
    while (number != 0)
    {
        digit = (number / 10) % 10; // start at second-to-last
        number /= 10;

        // If odd or even multiply and add or just add.
        if (position % 2 == parity)
        {

            digit = digit * 2; // take each digit and multiply by 2

            // if digit is more than 9 then minus 9
            if (digit > 9)
            {
                digit = digit - 9;
            }
            sum = sum + digit; // get sum of numbers multiplied
        }

        if (position % 2 != parity)
        {
            sum = sum + digit; // get sum of numbers added
        }

        final_sum = sum + last_digit; // add both sums together
        position++; // loop position and length
        length++;
    }

    // Check if sum ends in zero
    valid = final_sum % 10 == 0;

    // if first_digit is 4, and length is between 13 and 16  and checksum ends in zero - print VISA.
    if (first_digit == 4 && length >= 13 && length <= 16 && valid)
    {
        printf("VISA\n");
    }
    // if first two digits are 37 or 37, length is 15 and checksum ends in zero - print AMEX/
    else if ((first_two_digits == 34 || first_two_digits == 37) && length == 15 && valid)
    {
        printf("AMEX\n");
    }
    // if first two digits are between 51 and 55, length is 16 and checksum equals zero - print MASTERCARD
    else if (first_two_digits >= 51 && first_two_digits <= 55 && length == 16 && valid)
    {
        printf("MASTERCARD\n");
    }
    // if no cases are matched - print INVALID
    else
    {
        printf("INVALID\n");
    }

}