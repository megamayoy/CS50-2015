/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
   int right = n - 1;
   int left=0;
   int middle; 
      
   while(left<=right)
   {
      middle = left + ( right - left ) / 2;
      
      if(values[middle] == value)
      return true ;
      
      else if(value > values[middle])
      left = middle + 1;
      else
      right = middle - 1;
      
   
   
   }  
   
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int tmp;
    int index;
    for(int i = 1;i < n;i++)
    { 
      tmp=values[i];
      index = i;
      
      while(index != 0 && values[index - 1] > values[index] )
      {
         values[index] = values[index - 1];
         values[index - 1] = tmp;
         index--;
         tmp = values[index]; 
      }
    }
    return;
}
