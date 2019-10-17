#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

//1. define block size and byte
#define SIZEOFBLOCK 512;

typedef uint8_t BYTE;


int main(int argc, char *argv[])
{
//2. Check if there are the correct number of arguments
    if(argc != 2)
    {
        printf("Usage: copy infile outfile\n");
        return 1;
    }


    //3. Save the file name into storage from argv[1]
    char *infile = argv[1];

    //4. Open file FILE, check it is not NULL
      FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    //5. Define array buffer of size 512, type BYTE
    BYTE buffer[512];

    //6. Declare image counter to keep track of how many jpegs
    int imageCounter = 0;

    //7. Declare file name array of type char and size 8 (length of the file name
     char filename[8];
    //8. Declare file outptr as NULL
    FILE *outptr = NULL;

    //9. Start a while loop
    while (true)
    {
        //9a. Read bytes
        size_t numberBytesRead = (fread(buffer, sizeof(BYTE), 512, inptr));

        //9b. Check if end of file
        if(numberBytesRead < 512 && feof(inptr))
        {
            break;
        }

        //9c. Check for start of jpeg
        bool startNewJpeg = (buffer[0] == 0xff &&
        buffer[1] == 0xd8 &&
        buffer [2] == 0xff &&
        (buffer[3] & 0xf0) == 0xe0);

        //9d. If found a new jpeg, need to close previous jpeg
        if(startNewJpeg && outptr != NULL)
        {
            fclose(outptr);
            imageCounter++;
        }

        //9e. If found a jpeg, need to open file for writing
        if (startNewJpeg)
        {
            sprintf(filename, "%03i.jpg", imageCounter);
            outptr = fopen(filename, "w");

        }
        //9f. If there is an open file, write to the file
        if (outptr != NULL)
        {
            fwrite(buffer, sizeof(BYTE), numberBytesRead , outptr);
        }


    }

    //10. Close jpeg file
    fclose(outptr);
    //11. Close infile
    fclose(inptr);
    //12. Return success
     return 0;

} //end int main
