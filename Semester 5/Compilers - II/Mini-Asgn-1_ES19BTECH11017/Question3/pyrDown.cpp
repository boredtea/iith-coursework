#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

#define I_SIZE 640
#define K_SIZE 5

double image[I_SIZE][I_SIZE];
//double kernel[K_SIZE][K_SIZE] = {{1, 4, 6, 4, 1}, {4, 16, 24, 16, 4}, {6, 24, 36, 24, 6}, {4, 16, 24, 16, 4}, {1, 4, 6, 4, 1}};
// double kernel[K_SIZE][K_SIZE] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
double kernel[K_SIZE][K_SIZE] = {{0.00390625, 0.015625, 0.0234375, 0.015625, 0.00390625},
                                 {0.015625, 0.0625, 0.09375, 0.0625, 0.015625},
                                 {0.0234375, 0.09375, 0.140625, 0.09375, 0.0234375},
                                 {0.015625, 0.0625, 0.09375, 0.0625, 0.015625},
                                 {0.00390625, 0.015625, 0.0234375, 0.015625, 0.00390625}};

//pyrDown
void pyrDown()
{
    //Get the resolution of the image and the kernel
    int height, width, kernelSize;

    height = sizeof(image) / sizeof(image[0]);
    width = sizeof(image[0]) / sizeof(image[0][0]);

    kernelSize = sizeof(kernel) / sizeof(kernel[0]);

    int padding = (kernelSize - 1) / 2;

    //Pad the image to account for boundary conditions
    int heightFinal, widthFinal, heightRes, widthRes;

    heightRes = height;
    widthRes = width;

    heightFinal = ceil(height * 0.5);
    widthFinal = ceil(width * 0.5);

    //initialising all matrices

    //Initialise a padded array to store the image
    double padded[heightRes + 2 * padding][widthRes + 2 * padding];

    //If the image is not padded
    if (padding != 0)
    {
        for (int i = 0; i < height + 2 * padding; i++)
        {
            for (int j = i; j < width + 2 * padding; j++)
            {
                padded[i][j] = 0;
                padded[j][i] = 0;
            }
        }

        //Copy the image to the inner portion
        for (int i = 0; i < heightRes; i++)
        {
            for (int j = i; j < widthRes; j++)
            {
                padded[padding + i][padding + j] = image[i][j];
                padded[padding + j][padding + i] = image[j][i];
            }
        }
    }
    //If the image is padded
    else
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = i; j < width; j++)
            {
                padded[i][j] = image[i][j];
                padded[j][i] = image[j][i];
            }
        }
    }

    double gaussian[heightRes][widthRes];

    //Convolution
    for (int y = padding; y < heightRes + padding; y++)
    {
        for (int x = padding; x < widthRes + padding; x++)
        {
            double sum = 0;
            for (int i = kernelSize - 1, I = y - padding; i >= 0; i--, I++)
            {
                for (int j = kernelSize - 1, J = x - padding; j >= 0; j--, J++)
                {
                    sum += kernel[i][j] * padded[I][J];
                }
            }
            gaussian[y - padding][x - padding] = sum;
        }
    }

    //Initialise an output Image
    double output[heightFinal][widthFinal];
    for (int row = 0; row < heightFinal; row++)
    {
        for (int column = 0; column < widthFinal; column++)
        {
            output[row][column] = gaussian[2 * row][2 * column];
        }
    }

    ofstream fp("pyrdownOutput.txt");

    if (fp.is_open())
    {
        for (int row = 0; row < heightFinal; row++)
        { // stop loops if nothing to read
            for (int column = 0; column < widthFinal; column++)
            {
                fp << output[row][column] << " ";
                if (!fp)
                    break;
            }
            fp << endl;
        }
        fp.close();
    }
}

int main()
{
    ifstream fp("matrix.txt");
    if (!fp)
        return 1;
    for (int row = 0; row < I_SIZE; row++)
    { // stop loops if nothing to read
        for (int column = 0; column < I_SIZE; column++)
        {
            fp >> image[row][column];
            if (!fp)
                return 1;
        }
    }
    fp.close();
    pyrDown();

    return 0;
}