#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // Get RGB Values
            float originalRed = image[i][j].rgbtRed;
            float originalGreen = image[i][j].rgbtGreen;
            float originalBlue = image[i][j].rgbtBlue;

            // Calculate Average Value of Each Pixels
            int rgbtGrey = round((originalRed + originalGreen + originalBlue) / 3.0);

            // Set new RGB Values
            image[i][j].rgbtRed = rgbtGrey;
            image[i][j].rgbtGreen = rgbtGrey;
            image[i][j].rgbtBlue = rgbtGrey;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // Get RGB Values
            float originalRed = image[i][j].rgbtRed;
            float originalGreen = image[i][j].rgbtGreen;
            float originalBlue = image[i][j].rgbtBlue;

            // Get Sepia Values
            int sepiaRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            int sepiaGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            int sepiaBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);

            // Check for RGB Values Limits
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Set new RGB Values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Reverse the integer array
            RGBTRIPLE temp = image[i][j];
            image[i][j]  = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a Copy of the Image
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Set Variables
            int tempRed = 0;
            int tempGreen = 0;
            int tempBlue = 0;
            float counter = 0;

            // Neighbouring Pixels
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {

                    if (i + x < 0 || i + x > (height - 1) || j + y  < 0 || j + y > (width - 1))
                    {
                        continue;
                    }

                    // Get the new Values
                    tempRed += image[i + x][j + y].rgbtRed;
                    tempGreen += image[i + x][j + y].rgbtGreen;
                    tempBlue += image[i + x][j + y].rgbtBlue;

                    counter++;
                }
            }

            // Calculate the Average of neighbouring pixels
            temp[i][j].rgbtRed = round(tempRed / counter);
            temp[i][j].rgbtGreen = round(tempGreen / counter);
            temp[i][j].rgbtBlue = round(tempBlue / counter);
        }
    }

    // Copy into the original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Set new RGB Values
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue ;
        }
    }
}
