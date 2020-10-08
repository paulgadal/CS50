#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get the average value of the 3 rgb
            int gray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            
            // set the average value to all colors
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtRed = gray;
        }   
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, n = width / 2; j < n; j++)
        {
            // save pixel in a temporary value
            int rgbtBlueTmp = image[i][j].rgbtBlue;
            int rgbtGreenTmp = image[i][j].rgbtGreen;
            int rgbtRedTmp = image[i][j].rgbtRed;
               
            // swap pixels 
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            
            image[i][width - j - 1].rgbtBlue = rgbtBlueTmp;
            image[i][width - j - 1].rgbtGreen = rgbtGreenTmp;
            image[i][width - j - 1].rgbtRed = rgbtRedTmp;
        }   
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create an image with additionnal black borders to compute the 9 square on every pixel
    RGBTRIPLE imageTmp[height + 2][width + 2];
    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if ((i == 0) || (i == height + 1) || (j == 0) || (j == width + 1))
            {
                imageTmp[i][j].rgbtBlue = 0;
                imageTmp[i][j].rgbtGreen = 0;
                imageTmp[i][j].rgbtRed = 0;
            }
            else
            {
                imageTmp[i][j] = image[i - 1][j - 1];
            }
        }
    }
    
    // create an image to store the blur
    RGBTRIPLE imageBlur[height + 2][width + 2];
    
    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            int AvgBlue = 0;
            int AvgGreen = 0;
            int AvgRed = 0; 
            float divide = 0.0;

            if ((i == 1 && j == 1) || (i == 1 && j == width) || (i == height && j == 1) || (i == height && j == width))
            {
                // corner : divide by 4 
                divide = 4.0;
            }
            else if ((i == 1) || (i == height) || (j == 1) || (j == width)) 
            {
                // edge : divide by 6
                divide = 6.0;
            }
            else
            {
                // middle : divide by 9
                divide = 9.0;
            }
            
            // get the 9 squares
            for (int m = 0; m < 3; m++)
            {
                for (int n = 0; n < 3; n++)
                {
                    AvgBlue += imageTmp[i - 1 + m][j - 1 + n].rgbtBlue;
                    AvgGreen += imageTmp[i - 1 + m][j - 1 + n].rgbtGreen;
                    AvgRed += imageTmp[i - 1 + m][j - 1 + n].rgbtRed;
                }
            }
            
            imageBlur[i][j].rgbtBlue = round(AvgBlue / divide);
            imageBlur[i][j].rgbtGreen = round(AvgGreen / divide);
            imageBlur[i][j].rgbtRed =  round(AvgRed / divide);

        }
    }
    
    // asset blur to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imageBlur[i + 1][j + 1];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    
    // set Gx and Gy matrix
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    
    // create an image with additionnal black borders to compute the 9 square on every pixel
    RGBTRIPLE imageTmp[height + 2][width + 2];
    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if ((i == 0) || (i == height + 1) || (j == 0) || (j == width + 1))
            {
                imageTmp[i][j].rgbtBlue = 0;
                imageTmp[i][j].rgbtGreen = 0;
                imageTmp[i][j].rgbtRed = 0;
            }
            else
            {
                imageTmp[i][j] = image[i - 1][j - 1];
            }
        }
    }
    
    // create an image to store the edge
    RGBTRIPLE imageEdge[height + 2][width + 2];
    
    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            // initiate the 6 values for each pixel
            float GxBlue = 0.0;
            float GxGreen = 0.0;
            float GxRed = 0.0;
            
            float GyBlue = 0.0;
            float GyGreen = 0.0;
            float GyRed = 0.0;
            
            // get the 9 squares values around pixel
            for (int m = 0; m < 3; m++)
            {
                for (int n = 0; n < 3; n++)
                {
                    GxBlue += imageTmp[i - 1 + m][j - 1 + n].rgbtBlue * Gx[m][n];
                    GxGreen += imageTmp[i - 1 + m][j - 1 + n].rgbtGreen * Gx[m][n];
                    GxRed += imageTmp[i - 1 + m][j - 1 + n].rgbtRed * Gx[m][n];
                    
                    GyBlue += imageTmp[i - 1 + m][j - 1 + n].rgbtBlue * Gy[m][n];
                    GyGreen += imageTmp[i - 1 + m][j - 1 + n].rgbtGreen * Gy[m][n];
                    GyRed += imageTmp[i - 1 + m][j - 1 + n].rgbtRed * Gy[m][n];
                }
            }
            
            // compute the square root of Gx^2 and Gy^2
            int eBlue = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));
            int eGreen = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
            int eRed = round(sqrt(GxRed * GxRed + GyRed * GyRed));
            
            // check that edge value is below 255, else set it to 255
            if (eBlue > 255)
            {
                imageEdge[i][j].rgbtBlue = 255;
            }
            else
            {
                imageEdge[i][j].rgbtBlue = eBlue;
            }
            
            if (eGreen > 255)
            {
                imageEdge[i][j].rgbtGreen = 255;
            }
            else
            {
                imageEdge[i][j].rgbtGreen = eGreen;
            }

            if (eRed > 255)
            {
                imageEdge[i][j].rgbtRed = 255;
            }
            else
            {
                imageEdge[i][j].rgbtRed = eRed;
            }

        }
    }
    
    // asset edge to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imageEdge[i + 1][j + 1];
        }
    }
    return;
}
