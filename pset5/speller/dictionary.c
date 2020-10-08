// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"
#include <ctype.h>


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Number of elements loaded into the dictionnary
int element = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // hash word
    int h = hash(word);

    // check in the linked list if the word is inside     
    for (node *tmp = table[h]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // adapted from djb2 hash function: http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;
    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict != NULL)
    {
        // get each word of the dictionnary
        char *dictWord = malloc(sizeof(char) * (LENGTH + 1));
        while (fscanf(dict, "%s", dictWord) != EOF)
        {
            // create a new node to store the word
            node *n = malloc(sizeof(node));
            if (n != NULL)
            {
                strcpy(n->word, dictWord);
                n->next = NULL;

                // hash word
                int h = hash(n->word);

                //insert the new node at the begining of the linked list
                n->next = table[h];
                table[h] = n;
                
                // count elements of dictionnary
                element++;
                
            }
            else
            {
                return false;
            }
            
        }
        free(dictWord);
        fclose(dict);
        return true;
    }
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // get elements counted when load of dictionnary
    return element;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
