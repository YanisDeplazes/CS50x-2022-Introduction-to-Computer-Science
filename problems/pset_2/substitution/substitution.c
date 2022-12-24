#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

string convert_cypher(string key, string plaintext);

int main(int argc, string argv[])
{
    // Check that the user provies one command line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check that the key consists of 26 Characters
    if (strlen(argv[1]) != 26)
    {
        printf("The Key must contain 26 characters.\n");
        return 1;
    }

    // Checking Elements in ARG
    for (int i = 0; i < strlen(argv[1]); i++)
    {

        if (!isalpha(argv[1][i]))
        {
            printf("The key must contain only alphabetical characters\n");
            return 1;
        }
        for (int j = i + 1; j < strlen(argv[1]); j++)
        {
            if (toupper(argv[1][i] == toupper(argv[1][j])))
            {
                printf("The key can't contain repeated characters\n");
                return 1;
            }
        }
    }


    // Get Plaintext
    string plaintext = get_string("plaintext: ");

    // Print Cypher Function
    printf("ciphertext: %s", convert_cypher(argv[1], plaintext));
    printf("\n");

}

string convert_cypher(string key, string plaintext)
{
    for (int i = 0; i < strlen(plaintext); i++)
    {
        // Getting Chars
        if (isupper(plaintext[i]))
        {
            int letter = plaintext[i] - 65;
            plaintext[i] = toupper(key[letter]);
        }
        else if (islower(plaintext[i]))
        {
            int letter = plaintext[i] - 97;
            plaintext[i] = tolower(key[letter]);
        }
    }

    return plaintext;
}
