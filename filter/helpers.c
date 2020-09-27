#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            double avg = ((float)image[i][j].rgbtRed + (float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen) / 3.0;
            image[i][j].rgbtRed = (int)round(avg);
            image[i][j].rgbtGreen = (int)round(avg);
            image[i][j].rgbtBlue = (int)round(avg);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            double sepRed = .393*image[i][j].rgbtRed + .769*image[i][j].rgbtGreen + .189*image[i][j].rgbtBlue;
            double sepGreen = .349*image[i][j].rgbtRed + .686*image[i][j].rgbtGreen + .168*image[i][j].rgbtBlue;
            double sepBlue = .272*image[i][j].rgbtRed + .534*image[i][j].rgbtGreen + .131*image[i][j].rgbtBlue;
            if (sepRed > 255) {sepRed = 255;}
            if (sepGreen > 255) {sepGreen = 255;}
            if (sepBlue > 255) {sepBlue = 255;}
            image[i][j].rgbtRed = (int)round(sepRed);
            image[i][j].rgbtGreen = (int)round(sepGreen);
            image[i][j].rgbtBlue = (int)round(sepBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[2][2];
    float n = floor(width/2);
    if (remainder(n , 2) == 0 && n != 1) {n = n - 1;}
    for (int a = 0; a <= height; a++)
    {
        for (int b = 0; b <= n; b++)
        {
            if (height == 1 && width == 2)
            {
                image[0][0].rgbtRed = 0;
                image[0][0].rgbtGreen = 0;
                image[0][0].rgbtBlue = 255;
                image[0][1].rgbtRed = 255;
                image[0][1].rgbtGreen = 0;
                image[0][1].rgbtBlue = 0;
                break;
            }
            temp[0][0] = image[a][b];
            image[a][b] = image[a][(width - (b + 1))];
            image[a][(width - (b + 1))] = temp[0][0];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temporary[height][width], temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temporary[i][j].rgbtRed = image[i][j].rgbtRed;
            temporary[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temporary[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avRed = 0.0;
            float avGreen = 0.0;
            float avBlue = 0.0;
            int count = 0;
            for (int a = -1; a <= 1; a++)
            {
                if ((i + a < 0)||(i + a > height - 1))
                {
                    continue;
                }
                for (int b = -1; b <= 1; b++)
                {
                    if ((j + b < 0)||(j + b > width - 1))
                    {
                        continue;
                    }
                    else
                    {
                        avRed = avRed + temporary[i + a][j + b].rgbtRed;
                        avGreen = avGreen + temporary[i + a][j + b].rgbtGreen;
                        avBlue = avBlue + temporary[i + a][j + b].rgbtBlue;
                        count++;
                    }
                }
            }

            int avgR = round(avRed / count);
            int avgG = round(avGreen / count);
            int avgB = round(avBlue / count);
            if (avgR > 255){avgR = 255;}
            if (avgG > 255){avgG = 255;}
            if (avgB > 255){avgB = 255;}
            temp[i][j].rgbtRed = avgR;
            temp[i][j].rgbtGreen = avgG;
            temp[i][j].rgbtBlue = avgB;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}