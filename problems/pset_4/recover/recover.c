#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{

    // Check that there are two arguments
    if (argc != 2)
    {
        printf("Usage: IMAGE\n");
        return 1;
    }

    // Open file for reading
    FILE *input = fopen(argv[1], "r");

    // Check if the file is valid
    if (input == NULL)
    {
        printf("Could not open File\n");
        return 1;
    }

    // Store blocks of BLOCK_SIZE bytes in an array
    const int BLOCK_SIZE = 512;
    unsigned char buffer[BLOCK_SIZE];

    // Track number of images generated
    int count_image = 0;

    // File Pointer for recovered Images
    FILE *output = NULL;

    // Allocate memory for File
    char *image = malloc(8 * sizeof(char));

    while (fread(buffer, sizeof(char), BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        // Find the begining of an JPG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef)
        {
            // Create New Image file
            sprintf(image, "%03i.jpg", count_image);

            // Open Output File
            output = fopen(image, "w");

            // Increase Count of Images created
            count_image++;
        }

        // Write Image file
        if (output != NULL)
        {
            fwrite(buffer, sizeof(char), BLOCK_SIZE, output);
        }
    }


    // Close Files
    free(image);
    fclose(output);
    fclose(input);

    return 0;
}