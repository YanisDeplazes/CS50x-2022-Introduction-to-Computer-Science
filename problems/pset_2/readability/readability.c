#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


int main(void)
{
    // Get text as a string
    string text = get_string("Text: ");

    // Set Variables
    float letters = 0;
    float sentence = 0;
    float words = 1;

    // Loop
    for (int i = 0; i < strlen(text); i++)
    {

        // Counting the number of words in a string with counting the spaces
        if (isspace(text[i]))
        {
            words++;
        }

        // Counting the number of letters in a string with isalpha method
        if (isalpha(text[i]))
        {
            letters++;
        }

        // Counting the number of sentences in a string with the if method
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentence++;
        }
    }


    // Coleman-Liau index
    float l =  letters / words * 100;
    float s =  sentence / words * 100;
    int grade = round(0.0588 * l - 0.296 * s - 15.8);

    // Print
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }

}