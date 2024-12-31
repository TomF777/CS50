#include "helpers.h"
#include <math.h>
#include <string.h>

int calculate_matrices(int size, int first[size][size], int second[size][size])
{
    // multiply each element of 1st array with element in 2nd array
    // and calculate sum of all products

    int result = 0;

    // multiply 1st and 2nd matrices and save into result matrix
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            result += first[i][j] * second[i][j];
        }
    }

    return result;
}

int sobel_filter(int Gx, int Gy)
{
    // calculate Sobel filter

    int result = round(sqrt(pow((double) Gx, 2.0) + pow((double) Gy, 2.0)));
    if (result > 255)
        return 255;

    return result;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg_color;

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            avg_color =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Update pixel values
            image[i][j].rgbtRed = avg_color;
            image[i][j].rgbtGreen = avg_color;
            image[i][j].rgbtBlue = avg_color;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // temporary variable with one pixel data
    RGBTRIPLE pixel;

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        // reflect only horizontal pixels
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels
            pixel = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = pixel;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaGreen, sepiaBlue;

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute sepia values
            sepiaRed = round((image[i][j].rgbtRed * 0.393) + (image[i][j].rgbtGreen * 0.769) +
                             (image[i][j].rgbtBlue * 0.189));
            if (sepiaRed > 255)
                sepiaRed = 255;

            sepiaGreen = round((image[i][j].rgbtRed * 0.349) + (image[i][j].rgbtGreen * 0.686) +
                               (image[i][j].rgbtBlue * 0.168));
            if (sepiaGreen > 255)
                sepiaGreen = 255;

            sepiaBlue = round((image[i][j].rgbtRed * 0.272) + (image[i][j].rgbtGreen * 0.534) +
                              (image[i][j].rgbtBlue * 0.131));
            if (sepiaBlue > 255)
                sepiaBlue = 255;

            // Update pixel with sepia values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE image_copy[height][width];

    // row iteration
    for (int i = 0; i < height; i++)
    {
        // column iteration
        for (int j = 0; j < width; j++)
        {
            int sum_rgbtRed = 0, sum_rgbtGreen = 0, sum_rgbtBlue = 0, pixels_number = 0;

            // create row offset +-1 pixel for current pixel
            for (int i_row_offset = i - 1; i_row_offset <= i + 1; i_row_offset++)
            {
                // create column offset +-1 pixel for current pixel
                for (int j_col_offset = j - 1; j_col_offset <= j + 1; j_col_offset++)
                {
                    if (i_row_offset >= 0 && i_row_offset < height &&
                        j_col_offset >= 0 && j_col_offset < width)
                        {
                            // count number of adjacent pixels
                            pixels_number++;
                            // sum color value of adjacent pixels
                            sum_rgbtRed += image[i_row_offset][j_col_offset].rgbtRed;
                            sum_rgbtGreen += image[i_row_offset][j_col_offset].rgbtGreen;
                            sum_rgbtBlue += image[i_row_offset][j_col_offset].rgbtBlue;
                        }
                }
            }

            // calculate avarage for each color
            image_copy[i][j].rgbtRed = round((float) sum_rgbtRed / (float) pixels_number);
            image_copy[i][j].rgbtGreen = round((float) sum_rgbtGreen / (float) pixels_number);
            image_copy[i][j].rgbtBlue = round((float) sum_rgbtBlue / (float) pixels_number);
        }
    }

    // copy modified image_copy[][] array into original image[][]
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = image_copy[h][w];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    const int ARR_SIZE=3;

    // Create a copy of image
    RGBTRIPLE image_copy[height][width];

    // declare 2d arrays for Gx and Gy kernels
    int Gx_kernel[ARR_SIZE][ARR_SIZE] = {{-1, 0, 1},
                           {-2, 0, 2},
                           {-1, 0, 1}};

    int Gy_kernel[ARR_SIZE][ARR_SIZE] = {{-1, -2, -1},
                           {0, 0, 0},
                           {1, 2, 1}};
    int Gx, Gy;

    // temporary arrays
    int temp_arr_red[ARR_SIZE][ARR_SIZE];
    int temp_arr_green[ARR_SIZE][ARR_SIZE];
    int temp_arr_blue[ARR_SIZE][ARR_SIZE];

    // clear arrays
    memset(temp_arr_red, 0, ARR_SIZE * ARR_SIZE * (sizeof(int)));
    memset(temp_arr_green, 0, ARR_SIZE * ARR_SIZE * (sizeof(int)));
    memset(temp_arr_blue, 0, ARR_SIZE * ARR_SIZE * (sizeof(int)));

    // row iteration
    for (int row = 0; row < height; row++)
    {
        // column iteration
        for (int col = 0; col < width; col++)
        {

            // iterate around the current pixel (make copy of 9 pixels)
            for (int row_offset = row - 1, idx_row = 0; row_offset <= row + 1;
                 row_offset++, idx_row++)
            {

                for (int col_offset = col - 1, idx_col = 0; col_offset <= col + 1;
                     col_offset++, idx_col++)

                {
                    // edge/corner detection.
                    if (col_offset < 0 || row_offset < 0 ||
                        col_offset >= width || row_offset >= height)
                        {
                            temp_arr_red[idx_row][idx_col] = 0;
                            temp_arr_green[idx_row][idx_col] = 0;
                            temp_arr_blue[idx_row][idx_col] = 0;
                        }
                        else
                        {
                            // copy rgb value to temporary arrays
                            temp_arr_red[idx_row][idx_col] = image[row_offset][col_offset].rgbtRed;
                            temp_arr_green[idx_row][idx_col] = image[row_offset][col_offset].rgbtGreen;
                            temp_arr_blue[idx_row][idx_col] = image[row_offset][col_offset].rgbtBlue;
                        }

                }
            }

            // calculation for RED
            Gx = calculate_matrices(3, temp_arr_red, Gx_kernel);
            Gy = calculate_matrices(3, temp_arr_red, Gy_kernel);
            image_copy[row][col].rgbtRed = sobel_filter(Gx, Gy);

            // calculation for GREEN
            Gx = calculate_matrices(3, temp_arr_green, Gx_kernel);
            Gy = calculate_matrices(3, temp_arr_green, Gy_kernel);
            image_copy[row][col].rgbtGreen = sobel_filter(Gx, Gy);

            // calculation for BLUE
            Gx = calculate_matrices(3, temp_arr_blue, Gx_kernel);
            Gy = calculate_matrices(3, temp_arr_blue, Gy_kernel);
            image_copy[row][col].rgbtBlue = sobel_filter(Gx, Gy);
        }
    }

    // copy modified image_copy[][] array into original image[][]
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = image_copy[h][w];
        }
    }
}
