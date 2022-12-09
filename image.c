#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"

// open the file, create an ImagePPM, and return the pointer
// return NULL if the file cannot be opened

ImagePPM *readPPM(char *filename)
{
FILE *inputFile = NULL;
inputFile = fopen(filename, "r");
if(inputFile == NULL) return NULL;

ImagePPM *image = malloc(sizeof(struct _imagePPM));
//scanning out "magic identifier" P3
fscanf(inputFile, "%*s");

int width, height, max;
fscanf(inputFile, "%d%d%d", &width, &height, &max);

image->pixels = (struct _pixel **)malloc(height*sizeof(struct _pixel *));
for(int i = 0; i < height; i++){
image->pixels[i] = (struct _pixel*)malloc(width*sizeof(struct _pixel));
}

for(int i = 0; i < height; i++){
for(int j = 0; j < width; j++){
int red, green, blue;
fscanf(inputFile, "%d%d%d", &red, &green, &blue);
(&(image->pixels[i][j]))->red = red;
(&(image->pixels[i][j]))->green = green;
(&(image->pixels[i][j]))->blue = blue;
}
}

strcpy(image->magic, "P3");
image->maxVal = max;
image->numRows = height;
image->numCols = width;

fclose(inputFile);

return image;
}

// open the file and write the ImagePPM to the file
// return 1 on success
// return 0 if the file cannot be opened

int writePPM(ImagePPM *pImagePPM, char *filename)
{
FILE *outputFile = NULL;
outputFile = fopen(filename, "w");
if(outputFile == NULL) return 0;

fprintf(outputFile, "%s\n%d\t%d\n%d\n", 
pImagePPM->magic, pImagePPM->numCols, 
pImagePPM->numRows, pImagePPM->maxVal);

for(int i = 0; i < pImagePPM->numRows; i++){
for(int j = 0; j < pImagePPM->numCols; j++){
Pixel *temp = &(pImagePPM->pixels[i][j]);
fprintf(outputFile, "%d %d %d ",
temp->red, temp->green, temp->blue);
}
fprintf(outputFile, "\n");
}

fclose(outputFile);

return 1;
}

// free the ImagePPM and its pixels
// everything with a malloc needs a free

void freePPM(ImagePPM *pImagePPM)
{
for(int i = pImagePPM->numRows - 1; i >=0; i--){
free(pImagePPM->pixels[i]);
}
free(pImagePPM->pixels);
free(pImagePPM);

return;
}

// open the file, create an ImagePGM, and return the pointer
// return NULL if the file cannot be opened

ImagePGM *readPGM(char *filename)
{
FILE *inputFile = NULL;
inputFile = fopen(filename, "r");
if(inputFile == NULL) return NULL;

ImagePGM *image = malloc(sizeof(struct _imagePGM));
//scanning out "magic identifier" P3
fscanf(inputFile, "%*s");

int width, height, max;
fscanf(inputFile, "%d%d%d", &width, &height, &max);

image->pixels = (int **)malloc(height*sizeof(int*));
for(int i = 0; i < height; i++){
image->pixels[i] = (int*)malloc(width*sizeof(int));
}

for(int i = 0; i < height; i++){
for(int j = 0; j < width; j++){
int value;
fscanf(inputFile, "%d", &value);
image->pixels[i][j] = value;
}
}

strcpy(image->magic, "P2");
image->maxVal = max;
image->numRows = height;
image->numCols = width;

fclose(inputFile);

return image;
}

// open the file and write the ImagePGM to the file
// return 1 on success
// return 0 if the file cannot be opened

int writePGM(ImagePGM *pImagePGM, char *filename)
{
FILE *outputFile = NULL;
outputFile = fopen(filename, "w");
if(outputFile == NULL) return 0;

fprintf(outputFile, "%s\n%d\t%d\n%d\n", 
pImagePGM->magic, pImagePGM->numCols, 
pImagePGM->numRows, pImagePGM->maxVal);

for(int i = 0; i < pImagePGM->numRows; i++){
for(int j = 0; j < pImagePGM->numCols; j++){
fprintf(outputFile, "%d ", pImagePGM->pixels[i][j]);
}
fprintf(outputFile, "\n");
}

fclose(outputFile);

return 1;
}

// free the ImagePGM and its pixels
// everything with a malloc needs a free

void freePGM(ImagePGM *pImagePGM)
{
for(int i = pImagePGM->numRows - 1; i >=0; i--){
free(pImagePGM->pixels[i]);
}
free(pImagePGM->pixels);
free(pImagePGM);

return;
}

ImagePGM *convertToPGM(ImagePPM *pImagePPM)
{
int width, height, max;
width = pImagePPM->numCols;
height = pImagePPM->numRows;
max = pImagePPM->maxVal;

ImagePGM *image = malloc(sizeof(struct _imagePGM));
image->pixels = (int **)malloc(height*sizeof(int*));
for(int i = 0; i < height; i++){
image->pixels[i] = (int*)malloc(width*sizeof(int));
}
strcpy(image->magic, "P2");
image->numRows = height;
image->numCols = width;
image->maxVal = max;

for(int i = 0; i < height; i++){
for(int j = 0; j < width; j++){
int average = 0;
average += pImagePPM->pixels[i][j].red;
average += pImagePPM->pixels[i][j].green;
average += pImagePPM->pixels[i][j].blue;
average /= 3;
image->pixels[i][j] = average;
}
}

return image;
}

ImagePGM *shrinkPGM(ImagePGM *pImagePGM)
{
int oldWidth, oldHeight;
oldWidth = pImagePGM->numCols;
oldHeight = pImagePGM->numRows;

int width, height, max;
width = oldWidth/2;
height = oldHeight/2;
max = pImagePGM->maxVal;

ImagePGM *image = malloc(sizeof(struct _imagePGM));
image->pixels = (int **)malloc(height*sizeof(int*));
for(int i = 0; i < height; i++){
image->pixels[i] = (int*)malloc(width*sizeof(int));
}
strcpy(image->magic, "P2");
image->numRows = height;
image->numCols = width;
image->maxVal = max;

for(int i = 0; i < height; i++){
for(int j = 0; j < width; j++){
int average = 0;
average += pImagePGM->pixels[i*2][j*2];
average += pImagePGM->pixels[i*2][j*2+1];
average += pImagePGM->pixels[i*2+1][j*2];
average += pImagePGM->pixels[i*2+1][j*2+1];
average /= 4;
image->pixels[i][j] = average;
}
}

return image;
}
