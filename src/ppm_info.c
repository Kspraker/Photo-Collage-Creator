/*******************
*Kaleb Spraker
*CPSC 1020 001, F18
*ksprake@clemson.edu
********************/

//This file contains the functions needed to convert and read in information
#include "ppm_info.h"

//This function reads and stores the header information of the current
//ppm file.
header_t read_header(FILE* image_file)
{
  header_t header;
  fscanf(image_file, "%s ",     header.magicNum);
  fscanf(image_file, "%d %d ", &header.width, &header.height);
  fscanf(image_file, "%d ",    &header.maxVal);
  return header;
}

//This function takes that stored header data and writes it out to the file
//when called.
void write_header(FILE* out_file, header_t header)
{
 fprintf(out_file, "%s %d %d %d\n", header.magicNum, header.width,
 header.height, header.maxVal);
}

//This function calls the header and image data and stores it into the image
image_t* read_ppm(FILE* image_file)
{
 header_t header = read_header(image_file);
 image_t* image = read_pixels(image_file, header);

 return image;
}

//This function goes through the image ppm and reads-in/stores the red, green,
//and blue pixel color values.
image_t* read_pixels(FILE* image_file, header_t header)
{
  //calling allocate memory and passing in header
  image_t* image = allocate_memory(header);
  //Using unsigned char variables to fix the type
  unsigned char r, g ,b;
  int row, col;
  for (row = 0; row < header.height; row++)
  {
    for (col = 0; col < header.width; col++)
    {
      fscanf(image_file, "%c%c%c", &r, &g, &b);
      image->pixels[row][col].r = r;
      image->pixels[row][col].g = g;
      image->pixels[row][col].b = b;
    }
  }
  return image;
}

//This function simply allocates memory for the image, pixels in the image,
//and the rows.
image_t* allocate_memory(header_t header)
{
 int row;
 image_t* image = malloc(sizeof(image_t));
 image->pixels = malloc(sizeof(pixel_t*) * header.height);
 for (row = 0; row < header.height; row++)
 {
   image->pixels[row] = malloc(sizeof(pixel_t) * header.width);
 }

 //Setting the image header equal to the data in the current header for later
 //use.
 image->header = header;

 return image;
}

//Writes the collage, also creates the new images and frees memory
void writeCollage(FILE* out_file, image_t* image)
{
 int row, col;

 //Allocates memory fo the new image_t* variables
 image_t* newImage = malloc(sizeof(image_t));
 image_t* grayImage = malloc(sizeof(image_t));

 //Sets the height and width of the new images to desired values
 newImage->header.width = 340;
 newImage->header.height = 320;
 grayImage->header = newImage->header;

 //Allocates memory for the pixels
 newImage->pixels2 = malloc(sizeof(pixel_t*) * image->header.height);
 for (row = 0; row < newImage->header.height; row++)
 {
   newImage->pixels2[row] = malloc(sizeof(pixel_t) * image->header.width);
 }

 grayImage->pixels2 = malloc(sizeof(pixel_t*) * image->header.height);
 for (row = 0; row < newImage->header.height; row++)
 {
   grayImage->pixels2[row] = malloc(sizeof(pixel_t) * image->header.width);
 }

 //Resizes the image
 resizeImage(image, newImage);
 resizeImage(image, grayImage);

 //Converts the image to gray
 grayScaling(grayImage);

 //Mirrors the image down
 mirrorDown(newImage);
 mirrorDown(grayImage);

 //Writes the header for the collage
 write_header(out_file, image->header);

 //Prints the collage
 for(row = 0; row < image->header.height; row++)
 {
   for (col = 0; col < image->header.width; col++)
   {
     int nRow = row - (image->header.height - newImage->header.height - 20);
     int nCol;

     //If the current pixels are within the bounds, prints the new image
     if (col >= 20 && col < 360 && row > 620 && row < 940)
     {
       nCol = col - 20;
       fprintf(out_file, "%c%c%c", newImage->pixels2[nRow][nCol].r,
       newImage->pixels2[nRow][nCol].g, newImage->pixels2[nRow][nCol].b);
     }

     //Prints the new image again, right next to the last one
     else if (col >= 360 && col < 700  && row > 620 && row < 940)
     {
       nCol = col - 360;
       fprintf(out_file, "%c%c%c", grayImage->pixels2[nRow][nCol].r,
       grayImage->pixels2[nRow][nCol].g, grayImage->pixels2[nRow][nCol].b);
     }

     //If not within the area of interest, prints the old images pixels
     else
     {
       fprintf(out_file, "%c%c%c", image->pixels[row][col].r,
       image->pixels[row][col].g, image->pixels[row][col].b);
     }
   }
 }

 //Frees the memory for each row
 for(row = 0; row < image->header.height; row++)
 {
   free(image->pixels[row]);
 }
 //Frees the memory stored in the image pixels
 free(image->pixels);
 //Frees the memory stored in the image
 free(image);

 //Frees the memory for each row
 for(int row = 0; row < newImage->header.height; row++)
   {
     free(newImage->pixels2[row]);
   }
 //Frees the memory stored in the image pixels
 free(newImage->pixels2);
 //Frees the memory stored in the image
 free(newImage);

 //Frees the memory for each row
 for(int row = 0; row < grayImage->header.height; row++)
   {
     free(grayImage->pixels2[row]);
   }
 //Frees the memory stored in the image pixels
 free(grayImage->pixels2);
 //Frees the memory stored in the image
 free(grayImage);
}

//Function that resizes the image
void resizeImage(image_t* image, image_t* newImage)
{
  int row, col, nRow, nCol;
  //Calculates the relative width by dividing current width by desired width.
  //Same with height
  double newWidth = (double)image->header.width / newImage->header.width;
  double newHeight = (double)image->header.height / newImage->header.height;

  //Loops through the new image
  for (row = 0; row < newImage->header.height; row++)
  {
    for (col = 0; col < newImage->header.width; col++)
    {
      //Creating and setting the new row and col values to the old values
      //multiplied by the relative height and width respectively
      nRow = row * newHeight;
      nCol = col * newWidth;

      //This sets the pixel values for the new image equal to the pixels values
      //of the old image at the resize ratio placement
      newImage->pixels2[row][col] = image->pixels[nRow][nCol];
    }
  }
}

//Function that makes the new image gray
void grayScaling(image_t* newImage)
{
  int row, col;
  int colorSum;
  int grayColor;

  //Loops throught the new image's pixels
  for (row = 0; row < newImage->header.height; row++)
  {
    for (col = 0; col < newImage->header.width; col++)
    {
      //Adds the pixels values together to make a sum
      colorSum = newImage->pixels2[row][col].r + newImage->pixels2[row][col].g
      + newImage->pixels2[row][col].b;

      //Divides the sum by 3, getting an average color
      grayColor = colorSum / 3;

      //If the color is below 0, sets it to 0
      if (grayColor < 0)
      {
        grayColor = 0;
      }
      //If the color is above the max, sets it to the max
      if (grayColor > 255)
      {
        grayColor = 255;
      }

      //Sets the current r, g, and b value and sets them equal to the average
      newImage->pixels2[row][col].r = grayColor;
      newImage->pixels2[row][col].g = grayColor;
      newImage->pixels2[row][col].b = grayColor;
    }
  }
}

//Function mirrors the image
void mirrorDown(image_t* newImage)
{
  int row, col;

  //loops through the pixels of the second half of the newImage
  for (row = newImage->header.height / 2; row < newImage->header.height; row++)
  {
    for (col = 0; col < newImage->header.width; col++)
    {
      //Sets the pixels in the new image for the second half of the image equal
      //to the pixels
      newImage->pixels2[row][col] =
      newImage->pixels2[newImage->header.height - 1 - row][col];
    }
  }
}
