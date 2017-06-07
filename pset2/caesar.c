/* 
*  this programs encrypts a palin text using caesar cipher.  
* it takes a non zero value as a key 
* input format(./caesar <key(a number)>)
*/
# include<stdio.h>
# include<ctype.h>
# include<string.h>
# include<stdlib.h>
# include<cs50.h>
int main(int argc, string argv[])
{ 
 // stop the program if inouts are wrong 
    if ( argc != 2 || atoi(argv[1]) == 0)
    {
        printf("Usage: ./caesar <key>\n");
        return 1;   
    }
    
  // convert the key from string to int 
    int key = atoi(argv[1]);
    
    // stop the program if the key isn't a positive number
    if ( key < 0 )
    {
        printf("Key must be a non-negative integer\n");
        return 1;
    }
    
    string text = GetString();
// now we look for letters in the plain text
// we convert the letters from ascii form to alphabetical form
// whether it's a lowercase or uppercase we use ascii math
// to cipher the letter

    for( int i = 0; i < strlen(text); i++)
    {
        if ( isalpha(text[i]) != 0 )
        {  
   
            if ( islower( text[i] ) != 0 )
            { 
            // convert from ascii to alphabetical 
                text[i] -= 97; 
                text[i] = (text[i] + key) % 26;
                // convert to ascii 
                text[i] += 97; 
            }
      
            else if ( isupper(text[i]) != 0 )
            {
      // convert from ascii to alphabetical
                text[i] -= 65;  
                text[i] = ( text[i] + key ) % 26;
            // convert back to ascii
                text[i] += 65; 
      
            }
       }
    }
    printf("%s\n",text);

}

