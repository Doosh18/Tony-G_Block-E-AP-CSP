#include "helpers.h"
#include "stdlib.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    for (int line = 0; line < height; line++)
    {
        for (int column = 0; column < width; column++)
        {
            if (image[line][column].rgbtBlue == 0
                && image[line][column].rgbtGreen == 0
                && image[line][column].rgbtRed == 0)
            {
                image[line][column].rgbtBlue = rand()%255;
                image[line][column].rgbtGreen = rand()%255;
                image[line][column].rgbtRed = rand()%255;
            }
        }
    }
}
