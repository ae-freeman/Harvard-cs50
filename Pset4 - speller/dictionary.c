// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1]; //why plus one? -> to hold the end of string marker
    struct node *next;
}
node;

//declare variable to count the number of words in the dictionary
int number_words = 0;

// Represents a hash table -> setting up one hash table with type node. Later, will create 26 hashtables.
node *hashtable[N]; //[N = 26]

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return (tolower(word[0]) - 'a') % N;
    //modulo SIZE
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Initialize hash table with 26 indexes
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Buffer for a word
    char buffer[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", buffer) != EOF) //word is the variable in %s from fscan
    //function either returns true or eof.
    {


        //create a temporary node
        node *new_node = (node*)malloc(sizeof(node));

        strncpy(new_node->word, buffer, sizeof(buffer));

        //hash function
        int index = hash(buffer);

        // printf("New node->word: %s\n", new_node->word);

        //if the resulting index in hashtable is empty, assign it to the temp node
        if (hashtable[index] == NULL)
        {
            hashtable[index] = new_node;
            // printf("Hashtable head: %s\n", hashtable[index]->word);
        }

        //else append temp to the start of the linked list

        else
        {
            node *cursor_node = hashtable[index];
            // printf("Cursor node: %s\n", cursor_node->word);

            while(cursor_node->next != NULL)
            {
                // printf("Text = %s\n", cursor_node->word);
                cursor_node = cursor_node->next;

            }
            cursor_node->next = new_node;
            // printf("Cursor node next: %s\n", cursor_node->next->word);
        }

        number_words++;

}

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;


return false;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{

    return number_words;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{

    int hash_index_to_check = hash(word);
    // printf("Hash index to check: %i\n", hash_index_to_check);


    if (hashtable[hash_index_to_check] == NULL)
    {
        //if no linked list exists, word is automatically mispelt
        return false;
    }

    // printf("Head word: %s\n", hashtable[hash_index_to_check]->word);


    // A linked list does exist with at least one node
    node *cursor_node = hashtable[hash_index_to_check];


    while(cursor_node != NULL)
    {

        if((strcmp(word, cursor_node->word) == 0))
        {
            return true;
        }


        cursor_node = cursor_node->next;
    }


    return false;
}

void destroy(node *head)
{
    if (head->next != NULL)
    {
        destroy(head->next);
    }
    free(head);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
  for (int i = 0; i < N; i++)
  {
      if (hashtable[i] != NULL)
      {
          destroy(hashtable[i]);
      }
  }

  return true;
}


