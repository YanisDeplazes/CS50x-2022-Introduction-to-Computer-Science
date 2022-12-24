// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 10000; // 26 Default You will likely want to increase this depending on your own implementation of hash

int words_count = 0;
unsigned int value;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{

    // TODO
    value = hash(word);

    // Set the Value to the node
    node *cursor = table[value];

    // Go through the list
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // Modified djb2 algorithm http://www.cse.yorku.ca/~oz/hash.html

    unsigned long hash = 5381;
    int c;

    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    // Open File
    FILE *file = fopen(dictionary, "r");

    // Return false if File can't be opened
    if (file == NULL)
    {
        return false;
    }

    // Declaring Variable
    char word[LENGTH + 1];

    // Scan Dictionary for string until EOF
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory for new node
        node *node_new = malloc(sizeof(node));

        // Return false if malloc returns NULL
        if (node_new == NULL)
        {
            return false;
        }

        // Pointer to next node and word itself
        strcpy(node_new->word, word);

        // Hashing Value
        value = hash(word);
        if (table[value] == NULL)
        {
            // Point New Node to Null
            node_new->next = NULL;
            table[value] = node_new;
        }
        else
        {
            // Point New Node to Null
            node_new->next = table[value];
            table[value] = node_new;
        }

        // Increase Words Words Count
        words_count++;
    }

    // Close File
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (words_count > 0)
    {
        return words_count;
    }
    return 0;

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    // Iterate through buckets
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        if (i == N - 1 && cursor == NULL)
        {
            return true;
        }
    }
    return false;
}
