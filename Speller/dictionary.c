// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

void lowst(char *str)
{
   while(*str)
   {
      if ( *str >= 'A' && *str <= 'Z' )
      {
         *str = *str + 32;
      }
      str++;
   }
}

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1000000;

// Hash table
node *table[N];


//counter for size fumction
unsigned int cou = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *cur = table[index];
    while (cur != NULL)
    {
        if (strcasecmp(word, cur->word) == 0)
        {
            return true;
        }
        else
        {
            cur = cur->next;
        }
    }
    free(cur);
    return false;
}

// Hashes word to a number
// The well known djb2 Algorithm from computer scientist Dan Bernstein.
unsigned int hash(const char *word)
{
    char tarr[41];
    char *tee = tarr;
    strcpy(tee, word);
    lowst(tee);
    unsigned long hash = 5381;
    int c;
    while ((c = *tee++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        return false;
    }

    char temp_word_holder[LENGTH + 1];

    while(fscanf(file, "%s", temp_word_holder) != EOF)
    {
        //create a new node for each word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            free(new_node);
            return false;
        }
        strcpy(new_node->word, temp_word_holder);
        new_node->next = NULL;

        //hash word to obtain a hash value
        int ind = hash(temp_word_holder);

        //insert node into hash table at that location
        if (table[ind] == NULL)
        {
            table[ind] = new_node;
        }
        else
        {
            new_node->next = table[ind];
            table[ind] = new_node;
        }
        cou++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return cou;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    int i = 0;
    while (table[i] != NULL)
    {
        node *curs = table[i];
        node *temp = table[i];
        curs = curs->next;
        while (curs->next != NULL)
        {
            temp = curs;
            curs = curs->next;
            free(temp);
        }
        i++;
        free(curs);
        free(temp);
    }
    return true;
}
