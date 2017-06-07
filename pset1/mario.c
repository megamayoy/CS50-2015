#include <stdio.h> 
#include <cs50.h> 
// cs50 library is needed to use GetInt() function 
// that enables users to input an integer value

int main(void)
{  

    int height; 
   // prompting the user to input a non negative integer that doesn't exceed 23
  
    do
    { 
         // input the height of the pyramid
        printf("Height: ");
      
        height = GetInt();
      
    }
    while(height < 0 || height > 23);

   // printing the pyramid
    
    for( int i =0;i < height;i++)
    {

       // every row has (height+1) -(2+row) spaces 
        for(int y=0;y < (height + 1) - ( 2 + i );y++)
        {  
                                                        
       
            printf(" ");
       
        }
       
       // every row has 2+row hashes 
        for(int x=0;x < 2 + i;x++)
        {  
            printf("#");
        }
        printf("\n");
 

    }







}
