/*
*this program encrypts a plain text using vigenere cipher
*it's more secure than caesar cipher. it uses a key word instead
*of a number
* input format (./vigenere <key(a word)>)
*/ 
# include<stdio.h> 
# include<cs50.h>   
# include<stdlib.h>
# include<string.h>
# include<ctype.h>
int main(int argc, string argv[])
{ 
// check the inputs of the user 
// if the user doesn't input 2 argument which are the program name + key
// warn user and stop the program 
    if ( argc != 2)
    {
        printf("Usage: ./vigenere <word key>\n");
        return 1;
    }
    int counter=0;
    int key_size = strlen(argv[1]);
    
    // check if the key is word . else warn user and stop the program
    for(int i = 0; i < key_size; i++)
    {
        if ( isalpha( argv[1][i] ) == 0 )
        {
            counter++;
        }    
    }
    
    if ( counter != 0 )
    {
        printf("Keyword must only contain letters A-Z and a-z\n");
        return 1;
    }
        
        // converting the key to alphabetical 
        
    for(int i = 0; i < key_size; i++)
    { 
        if ( islower(argv[1][i]) != 0 )
        {
            argv[1][i] -= 97;
        }      
        else if ( isupper(argv[1][i]) != 0 )
        {
            argv[1][i] -= 65;
        }      
    }
        
 // get the plain text
    string text = GetString();
 
    int text_size = strlen(text);
    for(int i = 0, key = 0; i < text_size; i++, key++)
    { 
       // check if the letter text[i] is an alphabetical letter
        if ( isalpha(text[i]) != 0 )
        {  
   
            if ( islower( text[i] ) != 0 )
            { 
            // convert from ascii to alphabetical 
                text[i] -= 97; 
                text[i] = (text[i] + argv[1][key % key_size]) % 26;
                // convert to ascii 
                text[i] += 97; 
            }
      
            else if ( isupper(text[i]) != 0 )
            {
      // convert from ascii to alphabetical
                text[i] -= 65;  
                text[i] = ( text[i] + argv[1][key % key_size]  ) % 26;
            // convert back to ascii
                text[i] += 65; 
      
            }  
        }
// don't advance to next letter in the key unless text[i] is alphabetical 
        else 
            key--;
 
    }
   
    printf("%s\n",text);
      
} 
    
        
        
      


