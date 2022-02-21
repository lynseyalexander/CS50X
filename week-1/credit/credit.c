#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // create varibles
    long number;
    int digit;
    int length = 0;
    int position = 0;
    int sum; // total sum of all digits added together
    int parity = (length - 2) % 2; // even or odd
    long last_digit;
    int final_sum; // Adding the sum of digits not multiplied by 2.
    long first_digit;
    bool valid;

    // Ask user to input credit card number
    do
    {
        number = get_long("Number: ");
    }
    while (number <= 0);

    first_digit = number;
    last_digit = number;

    // Get the first digit of number and store in variable first_digit
    while(first_digit >= 10){
        first_digit /= 10;
    }

    while(last_digit >= 10){
        last_digit = last_digit % 10; // take last digit and store in variable.
    }

    //printf("last_number: %li\n", last_digit);
    //printf("number:: %li\n", number);

    // Luhn algorithm for checksum
    while(number != 0)
    {
        digit = (number / 10) % 10; // start at second-to-last
        number /= 10;

        // If odd or even multiply and add or just add.
        if(position % 2 == parity)
        {

            digit = digit * 2; // take each digit and multiply by 2

            // if digit is more than 9 then minus 9
            if (digit > 9)
            {
                digit = digit - 9;
            }
            sum = sum + digit; // get sum
        }

        if(position % 2 != parity)
        {
            sum = sum + digit;
        }

        final_sum = sum + last_digit; // add both sums together
        position++; // loop
        length++;
    }
    //printf("final_sum: %i\n", final_sum);

    // Check if sum ends in zero
    valid = final_sum % 10 == 0;
   // printf("valid: %d\n", valid);


    if(first_digit == 4 && length >= 13 && length <= 16 && valid){
        printf("VISA\n");
    } else if (length == 15 && valid) {
        printf("AMEX\n");
    } else if(length == 16 && valid){
        printf("MASTERCARD\n");
    } else {
        printf("INVALID\n");
    }


}



