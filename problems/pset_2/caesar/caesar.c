#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


string convert_cypher(int key, string plaintext);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage ./caesar key\n");
        return 1;
    }

    // Defining the Key
    string key = argv[1];

    // Check that the Input is a digit
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int k = atoi(key);

    // Get Plaintext
    string plaintext = get_string("plaintext: ");

    // Print Cypher Function
    printf("ciphertext: %s", convert_cypher(k, plaintext));
    printf("\n");

}

string convert_cypher(int key, string plaintext)
{
    for (int i = 0; i < strlen(plaintext); i++)
    {
        // Rotating Chars
        if (isupper(plaintext[i]))
        {
            plaintext[i] = (((plaintext[i] - 65) + key) % 26) + 65;
        }
        else if (islower(plaintext[i]))
        {
            plaintext[i] = (((plaintext[i] - 97) + key) % 26) + 97;
        }
    }

    return plaintext;
}