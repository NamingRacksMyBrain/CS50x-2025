// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 150000;

// Hash table
node *table[N];

// Keep track of number of words in dictionary
int SIZE = 0;

// Returns true if word is in dictionary, else false(case-insensitively)
bool check(const char *word)
{
    // Hash word
    int index = hash(word);

    // Access linked list
    node *head = table[index];

    // Traverse linked list
    node *cursor = head;
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
    int length = strlen(word);
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += (tolower(word[i]) * toupper(word[i]) + length * 103) * 3929; // One I figure out by myself
    }

    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // Read strings from file
    char word[LENGTH + 1];
    while (fscanf(dict, "%s", word) != EOF)
    {
        SIZE++;
        // Create a new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        strcpy(new_node->word, word);

        // Hash word
        int index = hash(word);

        // Insert node into hash table
        new_node->next = table[index];
        table[index] = new_node;
    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return SIZE;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // For each linked list in table
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = head;

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
