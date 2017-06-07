/* this program takes a full name and prints its initials
*
*/
# include <stdio.h>
# include <cs50.h> 
# include <ctype.h> 
# include <string.h>
int main(void)
{  
    string name=GetString();
    // always print the first letter of a name 
    printf("%c",toupper(name[0]));
    
    for( int i=0; i < strlen(name); i++)
    {  
    // if we find a space we print the letter next to it 
        if ( name[i] == ' ')
        { 
        // convert lower case letters to upper case if needed
            printf("%c",toupper(name[i + 1]));
       
        }
    }
   
   
    printf("\n");   
}



