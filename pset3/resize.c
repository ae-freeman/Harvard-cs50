////////RESIZE 24-BMPS BY A FACTOR OF N////////
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

//Check if there are the correct number of command arguments

    // if first argument is a positive int 1-100 AND
    //second argument is a bmp AND
    // third argument is name of resized version to be written

    int main(int argc, char *argv[])
    {
        // ensure proper usage
        if (argc != 3)
        {
            printf("Usage: copy infile outfile\n");
            return 1;
        }

        // remember factor to increase size by
        // int atoi n = argv[1];

        // remember filenames
        char *infile = argv[2];
        char *outfile = argv[3];

        // open input file
        FILE *inptr = fopen(infile, "r");
        if (inptr == NULL)
        {
            printf("Could not open %s.\n", infile);
            return 2;
        }

        // open output file
        FILE *outptr = fopen(outfile, "w");
        if (outptr == NULL)
        {
            fclose(inptr);
            printf("Could not create %s.\n", outfile);
            return 3;
        }

        // read infile's BITMAPFILEHEADER
        BITMAPFILEHEADER bf;
        fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

        // read infile's BITMAPINFOHEADER
        BITMAPINFOHEADER bi;
        fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

        // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
        if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
            bi.biBitCount != 24 || bi.biCompression != 0)
        {
            fclose(outptr);
            fclose(inptr);
            printf("Unsupported file format.\n");
            return 4;
        }

        // write outfile's BITMAPFILEHEADER
        fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

        // write outfile's BITMAPINFOHEADER
        fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

        // determine padding for scanlines
        int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;


        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;


                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), n, inptr);

              // resize horizontally



                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
        }

        // close infile
        fclose(inptr);

        // close outfile
        fclose(outptr);

        // success
        return 0;

}








// iterate over infile's scanlines: iterate over every row
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {

             //storing pixels in scanline here
            RGBTRIPLE pixel[bi.biWidth * n];

            //for (int row_tracker = 0; row_tracker < n; row_tracker ++)
            //{

            // iterate over pixels in scanline: iterate over each pixel in row
            for (int j = 0; j < old_biWidth; j++)
            {
                //add into an array, write that array n times


                for (int col_tracker = 0; col_tracker < n; col_tracker++)
                {
                // temporary storage
                RGBTRIPLE triple;


                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                //fwrite(&array, sizeof(array),1,outfile)???


                     // move file pointer back one pixel if not at last pixel
                    if (col_tracker != (n-1))
                    {
                        fseek(inptr, -sizeof(RGBTRIPLE), SEEK_CUR);
                    }
                }
            //}

            // skip over padding, if any
            fseek(inptr, old_padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < new_padding; k++)
            {
                fputc(0x00, outptr);
            }

               // move file pointer back to the beginning of the row if not at last row
            if (row_tracker != (n-1))
            {
                fseek(inptr, (-sizeof(RGBTRIPLE) * old_biWidth) - old_padding , SEEK_CUR);
            }
        }

        // close infile
        fclose(inptr);

        // close outfile
        fclose(outptr);

        // success
        return 0;

}
}
