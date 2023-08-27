// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include<strings.h>
#include<string.h>
#include "dictionary.h"
int k=0;
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hash_val = hash(word);
    node *cn = malloc(sizeof(node));
    cn = table[hash_val];
    while(cn != NULL)
    {
        if(strcasecmp(word,cn->word) == 0)
        {
            return true;
        }
        cn = cn->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    long sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }
    return sum % N;
    //return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //k=0;
   FILE *f = fopen(dictionary,"r");
   if(dictionary == NULL)
   {
       printf("Unable to open %s\n", dictionary);
       return false;
   }
   char words[LENGTH + 1];
   while(fscanf(f,"%s",words) != EOF)
   {
   fscanf(f,"%s",words);
   node *newnode = malloc(sizeof(node));
    if(newnode == NULL)
    {
        return false;
    }
        strcpy( newnode->word, words);
        int hash_val = hash(words);
        newnode->next = table[hash_val];
        table[hash_val] = newnode;
        k++;
   }
   fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return k;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
        while (n != NULL)
        {
            node *tmp = n;
            n = n->next;
            free(tmp);
        }
        if (n == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
