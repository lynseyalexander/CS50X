#include <stdio.h>
#include <cs50.h>

/*
Function asks for the users name.
Prints users name to screen.
*/
int main(void)
{
    string name = get_string("What's your name? ");
    printf("Hello, %s\n", name);
}