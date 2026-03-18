#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("File can't open\n");
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[BLOCK_SIZE];
    char filename[8] = "000.jpg";

    int i = -1;
    bool found_jpeg = false;
    FILE *img = fopen(filename, "w");

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // If start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            i++;
            found_jpeg = true;
            sprintf(filename, "%03i.jpg", i);

            // If first JPEG
            if (i == 0)
            {
                if (img != NULL)
                {
                    fwrite(buffer, 1, BLOCK_SIZE, img);
                }
            }
            // Not first JPEG
            else
            {
                fclose(img);
                img = fopen(filename, "w");
                if (img != NULL)
                {
                    fwrite(buffer, 1, BLOCK_SIZE, img);
                }
            }
        }
        // Not start of new JPEG
        else
        {
            // If already found JPEG
            if (found_jpeg == true)
            {
                fwrite(buffer, 1, BLOCK_SIZE, img);
            }
        }
    }
    // Close files
    fclose(img);
    fclose(card);
}
