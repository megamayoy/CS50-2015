/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdint.h>

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{ 
    char title[10];
    
    FILE* img;
    int nums_image = 0;
    FILE* inptr = fopen("card.raw","r");
    // check for errors
    if ( inptr == NULL)
    {
        return 2;
    }
    // allocate memory to store 512 bytes  
    uint8_t* block = malloc( 512 * sizeof(uint8_t));
    if (block == NULL)
    {
        return 4; 
    }
    // read 512 bytes from card.raw until EOF
    while( fread(block ,sizeof(uint8_t) ,512,inptr) == 512 )
    {   
// if it's a jpeg create a file to store it.  
        if ( block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff )
        {
            if ( block[3] == 0xe0 || block[3] == 0xe1)
            {
        // name the file with it's number.
                sprintf(title,"%03d.jpg", nums_image );
        // if it's not the firtst jpg,close the previous image    
                if (nums_image != 0 )
                {
                    fclose(img);
                } 
            
                img = fopen(title,"w");
                if ( img == NULL)
                {
                    return 5;
                }
                fwrite( block,sizeof(uint8_t),512,img);
                nums_image++; 
            }            
        }
        // if it's not a jpeg and not a garbage,write the block of data to img
        else
        {
            if (nums_image != 0)
            {
                fwrite( block,sizeof(uint8_t),512,img);             
            }               
        }  
              
    }
    // close files and free allocated memory
    fclose(img);
    fclose(inptr);
    free(block);
    
    return 0;       
}
