#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // create variables
    int height, row, column, gap;

    // Ask the user to input a value for height, must be between 0 and 8.
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    /* Create rows until the value of row is less than or equal to the value of height.
       Starts at row one instead of row 0 as row 0 would have no "#" symbol only a gap
       therefore nothing to display to the user. */
    for (row = 1; row <= height; ++row)
    {
        // Create gap(s) whilst the value of gap is less than the value of height.
        for (gap = 0; gap < height - row; ++gap)
        {
            printf(" ");
        }

        // Create a column until the value of column is less than the value of row.
        // Create the first half-pyramid.
        for (column = 0; column < row; ++column)
        {
            printf("#");
        }

        // Prints a new line.
        printf("\n");
    }

    // If code fails return zero.
    return 0;

}