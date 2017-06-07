/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>

#include "dictionary.h"
int num_of_words = 0;
FILE* dic;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int index = 0;
    node* crawl = root;
    int l;
    while( index <= LENGTH )
    {
        if(islower(word[index]))
        {
            l = word[index] - 'a';
        }
        else if(isupper(word[index]))
        {
            l = word[index] - 'A'; 
        }
        else if (word[index] == '\'')
        {
            l = 26;
        }
        
        if(word[index] != '\0')
        {  
            if(crawl->children[l] == NULL)
            {
                return false;
            }
            else
            {
                crawl = crawl->children[l];
                index++;
            }
            
        }
        else
        {
            if(crawl->is_word == true)
            {
                return true;
            }
            else
            {
            return false;
            }
        }

    }
    return true;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{  
     dic = fopen(dictionary,"r"); 
    if(dic == NULL)
    {
        printf("file is not opened");
        return false;
    }
    root = calloc(1,sizeof(node));
    node* walker = root;
    int n;
    for(char c = fgetc(dic) ; c != EOF ; c= fgetc(dic))
    {
        if(isalpha(c))
        {
            n = c-'a';
        }
        else if( c == '\'')
        {
            n = 26;
        }
        
        if(c != '\n')
        {
            if(walker->children[n] == NULL)
            {
                walker->children[n] = calloc(1,sizeof(node));    
            }
            walker = walker->children[n];
        }
        else
        {
            walker->is_word = 1;
            walker = root;
            num_of_words++;
        }
    }
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
       return num_of_words;
}
/**
*free nodes of dictionary
*
*/
void free_memory(node* current_node)
{
    for(int i = 0 ; i < 27 ; i++)
        {
            if(current_node->children[i] != NULL)
            {
                free_memory(current_node->children[i]);       
            }
           
        }
    free(current_node);
    
    return;    

}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{    

    free_memory(root);
    root = NULL;
      fclose(dic);
      return true ;
}
