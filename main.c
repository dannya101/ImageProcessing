#include <stdio.h>
#include <stdlib.h>
// Structure to hold grayscale pixel data
typedef struct {
    unsigned char value;
} PixelGray;
// Function to read a PGM image into a 2D array
PixelGray** readPGM(const char* filename, int* width, int* height);
// Function to write a 2D matrix as a PGM image
void writePGM(const char* filename, PixelGray** matrix, int* width, int* height);
// Function to threshold the image matrix
PixelGray** threshold(PixelGray** matrix, int* width, int* height);
// Function to rotate the image matrix
PixelGray** rotate(PixelGray** matrix, int* width, int* height);
int main() {
    int width, height; // variable to hold width and height. Use reference in other functions
    PixelGray** image_original = readPGM("lenna.pgm", &width, &height);
    // Now you have the grayscale image data in the 'image_original' 2D array
    // Access pixel data using image[row][col].value
    // For example, to access the pixel at row=2, col=3:
    // unsigned char pixel_value = image[2][3].value;
    // Create a new 2D array 'image_thresh' to store the threshold image
    printf("\nIn main function");
    printf("\n%d\n", image_original[0][0].value);
    printf("%d\n", image_original[10][10].value);
    printf("%d\n", image_original[20][0].value);
    printf("%d\n", image_original[10][20].value);

    PixelGray** image_thresh = threshold(image_original, &width, &height);
    //write the image data as "threshold.pgm"
    writePGM("threshold.pgm", image_thresh, &width, &height);
    // Create a new 2D array 'image_rotate' to store the rotated image
    PixelGray** image_rotate = rotate(image_original, &width, &height);
    //write the image data as "rotate.pgm"
    writePGM("rotate.pgm", image_rotate, &width, &height);
    image_rotate = rotate(image_rotate, &width, &height);
    //write the image data as "rotate_again.pgm"
    writePGM("rotate_again.pgm", image_rotate, &width, &height);
    // Free the allocated memory when you're done
    for (int i = 0; i < height; ++i) {
        free(image_original[i]);
        free(image_thresh[i]);
        free(image_rotate[i]);
    }
    free(image_original);
    free(image_thresh);
    free(image_rotate);
    return 0;
}

PixelGray** readPGM(const char* filename, int* width, int* height)
{
    FILE* file = NULL;
    file = fopen(filename, "r");
    if(file == NULL)
    {
        printf("Unable to open file\n");
        exit(1);
    }
    char format[3];
    //function to get format which is first value stored in file (P5)
    fscanf(file, "%s", format);
    
    //function to get the height and width in pixels of image which is on the second line of the lenna.pgm file
    //height = 512, width = 512
    fscanf(file, "%d %d", height, width);
    
    //here is where we get the size of the file
    int size;
    fscanf(file, "%d", &size);
    
    //have pointer point to next line
    fgetc(file);

    //here is where we use memory allocation
    PixelGray **matrix = (PixelGray**)malloc(*width * sizeof(PixelGray *));
    if (matrix == NULL) {
        printf("Error: Unable to allocate memory for rows\n");
    }
    for (int i = 0; i < *width; i++)
    {
        matrix[i] = (PixelGray *) malloc(*height * sizeof(PixelGray));
        if (matrix[i] == NULL) {
            printf("Error: Unable to allocate memory for columns in row %d\n", i);
        }
    }
    for(int i = 0; i < *width; i++) {
        for (int j = 0; j < *height; j++) {
             fread(&matrix[i][j].value, 1, 1, file);
        }
    }
    /*printf("\n%d\n", matrix[0][0].value);
    printf("%d\n", matrix[1][1].value);
    printf("%d\n", matrix[50][50].value);*/

    printf("\nIn read function!");
    printf("\n%d\n", matrix[0][0].value);
    printf("%d\n", matrix[10][10].value);
    printf("%d\n", matrix[20][0].value);
    printf("%d\n", matrix[10][20].value);


    fclose(file);
    return matrix;
}
void writePGM(const char* filename, PixelGray** matrix, int* width, int* height)
{
    FILE* file1 = NULL;
    file1 = fopen(filename, "w");
    if(file1 == NULL)
    {
        printf("Unable to open file\n");
        exit(1);
    }

    char format[3] = "P5";
    fprintf(file1, "%s\n", format);

    fprintf(file1, "%d %d\n", *height, *width);

    int size = 255;
    fprintf(file1, "%d\n", size);

    /*for (int i = 0; i < *width; i++)
    {
        matrix[i] = (PixelGray *) malloc(*height * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Error: Unable to allocate memory for columns in row %d\n", i);
        }
    }*/
    for(int idx = 0; idx < *width; idx++)
    {
        for (int i = 0; i < *height; i++)
        {
            fwrite(&matrix[idx][i].value, 1, 1, file1);
        }
    }

    printf("\nIn write function!");
    printf("\n%d\n", matrix[0][0].value);
    printf("%d\n", matrix[10][10].value);
    printf("%d\n", matrix[20][0].value);
    printf("%d\n", matrix[10][20].value);

    fclose(file1);
}
PixelGray** threshold(PixelGray** matrix, int* width, int* height)
{
    PixelGray **matrix1 = (PixelGray**)malloc(*width * sizeof(PixelGray*));
    for (int i = 0; i < *width; i++)
    {
        matrix1[i] = (PixelGray *) malloc(*height * sizeof(PixelGray));
        if (matrix1[i] == NULL) {
            printf("Error: Unable to allocate memory for columns in row %d\n", i);
        }
    }
    for(int idx = 0; idx < *width; idx++)
    {
        for (int i = 0; i < *height; i++)
        {
            if(matrix[idx][i].value > 80)
            {
                matrix1[idx][i].value = 255;
            }
            else
            {
                matrix1[idx][i].value = 0;
            }
        }
    }
    /*printf("\n%d\n", matrix1[0][0].value);
    printf("%d\n", matrix1[1][1].value);
    printf("%d\n", matrix1[50][50].value);*/

    printf("\nIn threshold function!");
    printf("\n%d\n", matrix1[0][0].value);
    printf("%d\n", matrix1[10][10].value);
    printf("%d\n", matrix1[20][0].value);
    printf("%d\n", matrix1[10][20].value);

    return matrix1;
}
PixelGray** rotate(PixelGray** matrix, int* width, int* height)
{
    PixelGray **matrix2 = (PixelGray **) malloc(*width * sizeof(PixelGray *));
    if(matrix == NULL) {
        printf("Error: Unable to allocate memory for rows\n");
    }
    for (int i = 0; i < *width; i++)
    {
        matrix2[i] = (PixelGray *) malloc(*height * sizeof(PixelGray));
        if (matrix2[i] == NULL) {
            printf("Error: Unable to allocate memory for columns in row %d\n", i);
        }
    }

    for(int idx = 0; idx < *width; idx++) {
        for (int i = 0; i < *height; i++) {
            matrix2[idx][i].value = matrix[i][idx].value;
        }
    }

    
    printf("\nIn rotate function!");
    printf("\n%d\n", matrix2[0][0].value);
    printf("%d\n", matrix2[10][10].value);
    printf("%d\n", matrix2[20][0].value);
    printf("%d\n", matrix2[10][20].value);

    return matrix2;
}
