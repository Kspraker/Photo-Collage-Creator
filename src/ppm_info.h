/*******************
*Kaleb Spraker
*CPSC 1020 001, F18
*ksprake@clemson.edu
********************/

#ifndef PPM_INFO
#define PPM_INFO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// First meaningful line of the PPM file
typedef struct header {
  char magicNum[3];
  int width, height, maxVal;
} header_t;

// Represents an RGB pixel with integer values between 0-255
typedef struct pixel {
  unsigned int r, g, b;
} pixel_t;

// PPM Image representation
typedef struct image {
  header_t header;
  pixel_t** pixels;

  //Added to help organization
  pixel_t** pixels2;

} image_t;

header_t read_header(FILE* image_file);

void write_header(FILE* out_file, header_t header);

image_t* read_ppm(FILE* image_file);

image_t* read_pixels(FILE* image_file, header_t header);

image_t* allocate_memory(header_t header);

//Prototype for writing the collage
void writeCollage(FILE* out_file, image_t* image);

//Prototype of the resizing
void resizeImage(image_t* image, image_t* newImage);

//Prototype for the graying
void grayScaling(image_t* newImage);

//Prototype for the Mirror
void mirrorDown(image_t* newImage);


#endif
