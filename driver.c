/*******************
*Kaleb Spraker
*CPSC 1020 001, F18
*ksprake@clemson.edu
********************/

//This project takes an image that I provide and resizes the image, mirrors it,
//and changes the color of that image to gray. It then outputs a collage of
//the old and new image.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/ppm_info.h"

int main(int argc, char* argv[])
{
  FILE *image_file, *out_file;

  //Checks to see that 3 files have been entered
  if(argc < 3)
  {
   printf("Usage Error: <executable> <inputFile> <outputFile>\n");
   return (-1);
  }

  image_file = fopen(argv[1], "r");

  //Checks to see if file can be opened
  if (image_file == NULL)
  {
   printf("Can't open input file %s!\n", argv[1]);
   return (-1);
  }


  out_file = fopen(argv[2], "w");

  //Checks to see if file can be opened/exists
  if (out_file == NULL)
  {
   printf("Can't open output file %s!\n", argv[2]);
   return (-1);
  }

  //Read ppm image
  image_t* image = read_ppm(image_file);

  //Writes the collage
  writeCollage(out_file, image);

  //Closes the files
  fclose(image_file);
  fclose(out_file);

  return 0;
}
