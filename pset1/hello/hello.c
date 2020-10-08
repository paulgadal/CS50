#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask user name
    string name = get_string("What is your name ?\n");
    // Display user name
    printf("hello, %s\n", name);
}