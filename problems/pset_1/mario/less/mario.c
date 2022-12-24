#include <cs50.h>
#include <stdio.h>

// Defining Functions
int get_number(string prompt);

int main(void)
{
    // Saving Height as int var
    int height = get_number("Height: ");
    for (int i = 0; height > i; i++)
    {

        // Get Number of Spaces
        for (int spaces = height - i - 2; spaces >= 0; spaces--)
        {
            printf(" ");
        }

        // Get Number of Hashes
        for (int hashes = 0; hashes <= i; hashes++)
        {
            printf("#");
        }

        // Starting new Line
        printf("\n");

    }
}

// Get Height
int get_number(string prompt)
{
    int height;
    do
    {
        height = get_int("%s", prompt);
    }
    while (height < 1 || height > 8);
    return height;
}