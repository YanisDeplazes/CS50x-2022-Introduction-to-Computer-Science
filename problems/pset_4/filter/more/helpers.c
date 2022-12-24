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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a Copy of the Image
    RGBTRIPLE temp[height][width];

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // Set Variables
            int gxRed = 0;
            int gxGreen = 0;
            int gxBlue = 0;

            int gyRed = 0;
            int gyGreen = 0;
            int gyBlue = 0;

            // Neighbouring Pixels
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    if (i + x < 0 || i + x > (height - 1) || j + y  < 0 || j + y > (width - 1))
                    {
                        continue;
                    }

                    // Calculating Gx
                    gxRed += image[i + x][j + y].rgbtRed * gx[x + 1][y + 1];
                    gxGreen += image[i + x][j + y].rgbtGreen * gx[x + 1][y + 1];
                    gxBlue += image[i + x][j + y].rgbtBlue * gx[x + 1][y + 1];

                    // Calculating Gy
                    gyRed += image[i + x][j + y].rgbtRed * gy[x + 1][y + 1];
                    gyGreen += image[i + x][j + y].rgbtGreen * gy[x + 1][y + 1];
                    gyBlue += image[i + x][j + y].rgbtBlue * gy[x + 1][y + 1];
                }
            }

            // Calculate the Square root
            int rgbtRed = round(sqrt(gxRed * gxRed + gyRed * gyRed));
            int rgbtGreen = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int rgbtBlue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));

            // Check for RGB Values Limits
            if (rgbtRed > 255)
            {
                rgbtRed = 255;
            }

            if (rgbtGreen > 255)
            {
                rgbtGreen = 255;
            }

            if (rgbtBlue > 255)
            {
                rgbtBlue = 255;
            }

            // Set the RGB Values
            temp[i][j].rgbtRed = rgbtRed;
            temp[i][j].rgbtGreen = rgbtGreen;
            temp[i][j].rgbtBlue = rgbtBlue;

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
