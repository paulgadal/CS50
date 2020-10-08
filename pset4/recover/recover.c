#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;
void writeJPEG(int i, BYTE *buffer);


int main(int argc, char *argv[])
{

    // Check for invalid usage
    if (argc < 2 || argc >= 3)
    {
        printf("Usage: recover [filename ...]\n");
        return 1;
    }
    
    // Open raw file and check for successful operation
    char *rawfile = argv[1];
    FILE *file = fopen(rawfile, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", rawfile);
        return 1;
    }

    
    // set buffer that will contain jpeg data
    BYTE *buffer = malloc(sizeof(BYTE) * 512);
    int i = 0;
    int start = 0;
    
    // while there is something to read in the raw file
    while (fread(buffer, sizeof(BYTE), 512, file) == 512)
    {
        // detect the begining of a jpeg file
        if ((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xef) == 0xe0))
        {   
            // first file to be detected
            if (start == 0)
            {
                writeJPEG(i, buffer);
                start = 1;
            }
            // new file detected
            else
            {
                i++;
                writeJPEG(i, buffer);
            }
        } 
        else if (start == 1)
        {
            writeJPEG(i, buffer);
        }
    }
    
    free(buffer);
}


void writeJPEG(int i, BYTE *buffer)
{
    // set the filename to the number of image
    char *filename = malloc(sizeof(8));
    sprintf(filename, "%03i.jpg", i);
    
    // open the file and append the content of buffer inside
    FILE *img = fopen(filename, "a");
    fwrite(buffer, sizeof(BYTE), 512, img);    
    
    // close file
    fclose(img);
}