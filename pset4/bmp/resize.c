/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }
    int factor = atoi(argv[1]);
    if ( factor < 1 || factor > 100 )
    {
        printf("inter a factor between 1 and 100\n");
        return 4;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    // make a copy of the BITMAPINFOHEADER
    BITMAPINFOHEADER newbi = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

  

    // adjust the BITMAPINFOHEADER before writing to the outfile
    newbi.biWidth = newbi.biWidth * factor;
    newbi.biHeight = newbi.biHeight * factor;
    int newpadding = (4 - (newbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
     
    newbi.biSizeImage = (newbi.biWidth * sizeof(RGBTRIPLE) * abs(newbi.biHeight)) + (newpadding * abs(newbi.biHeight));
    // adjust the BITMAPFILEHEADER
    bf.bfSize = 54 + newbi.biSizeImage;
     
       // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&newbi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
   // malloc a chunk of memeory to store rows of pixels
    RGBTRIPLE* store = malloc(newbi.biWidth * sizeof(RGBTRIPLE));
    if (store == NULL)
    { 
        printf("error in allocating memory");
        return 2;
     } 
       
    int index = 0;
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {    
        index = 0;
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {   
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            // copying pixels 
            for(int x = 0 ;x < factor;x++)
            {
                store[index] = triple;
                index++;
            }
          
        }
        
        // copying vertically with padding
        
        for(int d = 0 ;d < factor ; d++)
        {
            fwrite(store,sizeof(RGBTRIPLE),newbi.biWidth,outptr);
           // add padding
           
            for (int k = 0; k < newpadding; k++)
            {
                fputc(0x00, outptr);
            }
           
           
        }
        
        

        // skip over padding in the input file, if any
        fseek(inptr, padding, SEEK_CUR);

       
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);
    // free memory
    free(store);
    // that's all folks
    return 0;
}
