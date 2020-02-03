#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Please enter exactly one command-line argument.\n");
        return 1;
    }

    char *infile = argv[1];

    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    BYTE buffer[512];
    char fileName[1001];
    int fileCounter = 0;

    fread(&buffer, 1, 512, inptr);
    while (!(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0))
    {
        fread(&buffer, 1, 512, inptr);
    }

    int endofFile = 0;
    while (endofFile == 0)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(fileName, "%03i.jpg", fileCounter);
            fileCounter++;

            FILE *outptr = fopen(fileName, "w");

            fwrite(&buffer, 1, 512, outptr);
            fread(&buffer, 1, 512, inptr);
            while (!(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) && endofFile == 0)
            {
                fwrite(&buffer, 1, 512, outptr);
                if (fread(&buffer, 1, 512, inptr) != 512)
                {
                    endofFile = 1;
                }
            }
            fclose(outptr);
        }
    }
    fclose(inptr);

    return 0;
}
