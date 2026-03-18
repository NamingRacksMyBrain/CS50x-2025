#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // For each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average pixel value
            int aver =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Set each color value to the average value
            image[i][j].rgbtRed = aver;
            image[i][j].rgbtGreen = aver;
            image[i][j].rgbtBlue = aver;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Create buffer
    RGBTRIPLE buffer[height][width];

    // For each row
    for (int i = 0; i < height; i++)
    {
        // Swap pixels on horizontally opposite sides
        for (int j = 0; j < width; j++)
        {
            buffer[i][j] = image[i][width - j - 1];
        }
    }

    // Copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = buffer[i][j];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create buffer1: Copy with a black edge
    RGBTRIPLE buffer1[height + 2][width + 2];

    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (i == 0 || i == height + 1 || j == 0 || j == width + 1)
            {
                buffer1[i][j].rgbtRed = 0;
                buffer1[i][j].rgbtGreen = 0;
                buffer1[i][j].rgbtBlue = 0;
            }
            else
            {
                buffer1[i][j] = image[i - 1][j - 1];
            }
        }
    }

    // Create buffer2
    RGBTRIPLE buffer2[height][width];
    // For each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // For Red
            int sumR = buffer1[i][j].rgbtRed + buffer1[i][j + 1].rgbtRed +
                       buffer1[i][j + 2].rgbtRed + buffer1[i + 1][j].rgbtRed +
                       buffer1[i + 1][j + 1].rgbtRed + buffer1[i + 1][j + 2].rgbtRed +
                       buffer1[i + 2][j].rgbtRed + buffer1[i + 2][j + 1].rgbtRed +
                       buffer1[i + 2][j + 2].rgbtRed;

            // Corner
            if ((i == 0 || i == height - 1) && (j == 0 || j == width - 1))
            {
                buffer2[i][j].rgbtRed = round(sumR / 4.0);
            }
            // Edge(not corners)
            else if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                buffer2[i][j].rgbtRed = round(sumR / 6.0);
            }
            // Middle
            else
            {
                buffer2[i][j].rgbtRed = round(sumR / 9.0);
            }

            // For Green
            int sumG = buffer1[i][j].rgbtGreen + buffer1[i][j + 1].rgbtGreen +
                       buffer1[i][j + 2].rgbtGreen + buffer1[i + 1][j].rgbtGreen +
                       buffer1[i + 1][j + 1].rgbtGreen + buffer1[i + 1][j + 2].rgbtGreen +
                       buffer1[i + 2][j].rgbtGreen + buffer1[i + 2][j + 1].rgbtGreen +
                       buffer1[i + 2][j + 2].rgbtGreen;

            // Corner
            if ((i == 0 || i == height - 1) && (j == 0 || j == width - 1))
            {
                buffer2[i][j].rgbtGreen = round(sumG / 4.0);
            }
            // Edge(not corners)
            else if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                buffer2[i][j].rgbtGreen = round(sumG / 6.0);
            }
            // Middle
            else
            {
                buffer2[i][j].rgbtGreen = round(sumG / 9.0);
            }

            // For Blue
            int sumB = buffer1[i][j].rgbtBlue + buffer1[i][j + 1].rgbtBlue +
                       buffer1[i][j + 2].rgbtBlue + buffer1[i + 1][j].rgbtBlue +
                       buffer1[i + 1][j + 1].rgbtBlue + buffer1[i + 1][j + 2].rgbtBlue +
                       buffer1[i + 2][j].rgbtBlue + buffer1[i + 2][j + 1].rgbtBlue +
                       buffer1[i + 2][j + 2].rgbtBlue;

            // Corner
            if ((i == 0 || i == height - 1) && (j == 0 || j == width - 1))
            {
                buffer2[i][j].rgbtBlue = round(sumB / 4.0);
            }
            // Edge(not corners)
            else if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                buffer2[i][j].rgbtBlue = round(sumB / 6.0);
            }
            // Middle
            else
            {
                buffer2[i][j].rgbtBlue = round(sumB / 9.0);
            }
        }
    }

    // Copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = buffer2[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create buffer1: Copy with a black edge
    RGBTRIPLE buffer1[height + 2][width + 2];

    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (i == 0 || i == height + 1 || j == 0 || j == width + 1)
            {
                buffer1[i][j].rgbtRed = 0;
                buffer1[i][j].rgbtGreen = 0;
                buffer1[i][j].rgbtBlue = 0;
            }
            else
            {
                buffer1[i][j] = image[i - 1][j - 1];
            }
        }
    }

    // Create buffer2
    RGBTRIPLE buffer2[height][width];
    // For each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // For Red
            int gxR = -1 * buffer1[i][j].rgbtRed + buffer1[i][j + 2].rgbtRed -
                      2 * buffer1[i + 1][j].rgbtRed + 2 * buffer1[i + 1][j + 2].rgbtRed -
                      buffer1[i + 2][j].rgbtRed + buffer1[i + 2][j + 2].rgbtRed;
            int gyR = -1 * buffer1[i][j].rgbtRed - 2 * buffer1[i][j + 1].rgbtRed -
                      buffer1[i][j + 2].rgbtRed + buffer1[i + 2][j].rgbtRed +
                      2 * buffer1[i + 2][j + 1].rgbtRed + buffer1[i + 2][j + 2].rgbtRed;
            double tmpR = sqrt(gxR * gxR + gyR * gyR);
            if (tmpR > 255)
            {
                buffer2[i][j].rgbtRed = 255;
            }
            else
            {
                buffer2[i][j].rgbtRed = round(tmpR);
            }

            // For Green
            int gxG = -1 * buffer1[i][j].rgbtGreen + buffer1[i][j + 2].rgbtGreen -
                      2 * buffer1[i + 1][j].rgbtGreen + 2 * buffer1[i + 1][j + 2].rgbtGreen -
                      buffer1[i + 2][j].rgbtGreen + buffer1[i + 2][j + 2].rgbtGreen;
            int gyG = -1 * buffer1[i][j].rgbtGreen - 2 * buffer1[i][j + 1].rgbtGreen -
                      buffer1[i][j + 2].rgbtGreen + buffer1[i + 2][j].rgbtGreen +
                      2 * buffer1[i + 2][j + 1].rgbtGreen + buffer1[i + 2][j + 2].rgbtGreen;
            double tmpG = sqrt(gxG * gxG + gyG * gyG);
            if (tmpG > 255)
            {
                buffer2[i][j].rgbtGreen = 255;
            }
            else
            {
                buffer2[i][j].rgbtGreen = round(tmpG);
            }

            // For Blue
            int gxB = -1 * buffer1[i][j].rgbtBlue + buffer1[i][j + 2].rgbtBlue -
                      2 * buffer1[i + 1][j].rgbtBlue + 2 * buffer1[i + 1][j + 2].rgbtBlue -
                      buffer1[i + 2][j].rgbtBlue + buffer1[i + 2][j + 2].rgbtBlue;
            int gyB = -1 * buffer1[i][j].rgbtBlue - 2 * buffer1[i][j + 1].rgbtBlue -
                      buffer1[i][j + 2].rgbtBlue + buffer1[i + 2][j].rgbtBlue +
                      2 * buffer1[i + 2][j + 1].rgbtBlue + buffer1[i + 2][j + 2].rgbtBlue;
            double tmpB = sqrt(gxB * gxB + gyB * gyB);
            if (tmpB > 255)
            {
                buffer2[i][j].rgbtBlue = 255;
            }
            else
            {
                buffer2[i][j].rgbtBlue = round(tmpB);
            }
        }
    }

    // Copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = buffer2[i][j];
        }
    }

    return;
}
