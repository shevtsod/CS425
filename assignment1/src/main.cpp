#include <iostream>

#include "file.h"
#include "image.h"

////////////////////////////////////////////////////////////////////////////////
// CONSTANTS
////////////////////////////////////////////////////////////////////////////////

// File paths

const char* FILE_PATH_IN = "./in/rose.raw";

const char* FILE_PATH_OUT_P1_1 = "./out/p1_rose_128x128.raw";
const char* FILE_PATH_OUT_P1_2 = "./out/p1_rose_64x64.raw";
const char* FILE_PATH_OUT_P1_3 = "./out/p1_rose_32x32.raw";

const char* FILE_PATH_OUT_P2_1 = "./out/p2_rose_2bits.raw";
const char* FILE_PATH_OUT_P2_2 = "./out/p2_rose_3bits.raw";
const char* FILE_PATH_OUT_P2_3 = "./out/p2_rose_4bits.raw";

const char* FILE_PATH_OUT_P3 = "./out/p3_histogram_rose.raw";
const char* FILE_PATH_OUT_P3_P2_1 = "./out/p3_histogram_rose_p2_2bits.raw";
const char* FILE_PATH_OUT_P3_P2_2 = "./out/p3_histogram_rose_p2_3bits.raw";
const char* FILE_PATH_OUT_P3_P2_3 = "./out/p3_histogram_rose_p2_4bits.raw";

////////////////////////////////////////////////////////////////////////////////
// PROGRAM 1
////////////////////////////////////////////////////////////////////////////////

/**
 * Runs program for "Programming 1" question in Assignment 1.
 *
 * Problem statement:
 *   Resize the image to 128x128, 64x64, and 32x32 pixels.
 */
void program1(unsigned char imageIn[][image::COLS]) {
  std::cout << "Running \"Programming 1\" ..." << std::endl;

  // Buffers for holding output image data
  unsigned char imageOut1[image::ROWS / 2][image::COLS / 2];
  unsigned char imageOut2[image::ROWS / 4][image::COLS / 4];
  unsigned char imageOut3[image::ROWS / 8][image::COLS / 8];

  // Downscale first image to ROWS / 2 x COLS / 2
  image::downscale(&imageIn[0][0], &imageOut1[0][0], image::ROWS, image::COLS,
                   2);
  // Downscale second image to ROWS / 4 x COLS / 4
  image::downscale(&imageIn[0][0], &imageOut2[0][0], image::ROWS, image::COLS,
                   4);
  // Downscale third image to ROWS / 8 x COLS / 8
  image::downscale(&imageIn[0][0], &imageOut3[0][0], image::ROWS, image::COLS,
                   8);

  // Write outputs to files
  file::write(FILE_PATH_OUT_P1_1, (char*)&imageOut1[0][0],
              image::ROWS / 2 * image::COLS / 2);
  file::write(FILE_PATH_OUT_P1_2, (char*)&imageOut2[0][0],
              image::ROWS / 4 * image::COLS / 4);
  file::write(FILE_PATH_OUT_P1_3, (char*)&imageOut3[0][0],
              image::ROWS / 8 * image::COLS / 8);

  // Q: What are the effects of reducing the size of an image?
  // A: The smaller the image becomes, the more detail is lost and the harder
  //    it becomes to discern the object that is being depicted. This is because
  //    the same information that is represented by multiple pixels in a higher
  //    resolution image is reduced to a single pixel in the lower resolution
  //    image.
}

////////////////////////////////////////////////////////////////////////////////
// PROGRAM 2
////////////////////////////////////////////////////////////////////////////////

/**
 * Runs program for "Programming 2" question in Assignment 1.
 *
 * Problem statement:
 *   Create three different quantized versions of the image:
 *    1. Set the 2 lowest order bits to 0.
 *    2. Set the 3 lowest order bits to 0.
 *    3. Set the 4 lowest order bits to 0.
 */
void program2(unsigned char imageIn[][image::COLS]) {
  std::cout << "Running \"Programming 2\" ..." << std::endl;

  // Buffers for holding output image data
  unsigned char imageOut1[image::ROWS][image::COLS];
  unsigned char imageOut2[image::ROWS][image::COLS];
  unsigned char imageOut3[image::ROWS][image::COLS];

  // Unset 2 lowest order bits in first image
  image::reduceQuantization(&imageIn[0][0], &imageOut1[0][0], image::ROWS,
                            image::COLS, 2);
  // Unset 3 lowest order bits in second image
  image::reduceQuantization(&imageIn[0][0], &imageOut2[0][0], image::ROWS,
                            image::COLS, 3);
  // Unset 4 lowest order bits in third image
  image::reduceQuantization(&imageIn[0][0], &imageOut3[0][0], image::ROWS,
                            image::COLS, 4);

  // Write outputs to files
  file::write(FILE_PATH_OUT_P2_1, (char*)&imageOut1[0][0],
              image::ROWS * image::COLS);
  file::write(FILE_PATH_OUT_P2_2, (char*)&imageOut2[0][0],
              image::ROWS * image::COLS);
  file::write(FILE_PATH_OUT_P2_3, (char*)&imageOut3[0][0],
              image::ROWS * image::COLS);

  // Q: What are the effects of reducing the number of bits of each pixel?
  // A: Reducing the number of bits per pixel reduces the number of grey levels
  //    in a greyscale image. As a result, gradients start appearing as "bands"
  //    rather than smooth transitions between two grey levels. Some details
  //    may be lost as pixels with similar grey levels are blended into the
  //    same grey level. For example, an image with a single bit per pixel has
  //    only two grey levels available.
}

////////////////////////////////////////////////////////////////////////////////
// PROGRAM 3
////////////////////////////////////////////////////////////////////////////////

/**
 * Runs program for "Programming 3" question in Assignment 1.
 *
 * Problem statement:
 *   Output a histogram of the image in 256x256 pixels. The background has value
 *   255, and columns value 0. Run this program with `rose.raw` and the three
 *   images generated in step 2.
 */
void program3(unsigned char imageIn[][image::COLS]) {
  std::cout << "Running \"Programming 3\" ..." << std::endl;

  // Buffer for holding input image data from "Programming 2" question
  unsigned char imageInP21[image::ROWS][image::COLS];
  unsigned char imageInP22[image::ROWS][image::COLS];
  unsigned char imageInP23[image::ROWS][image::COLS];

  // Open images from "Programming 2" question
  file::read(FILE_PATH_OUT_P2_1, (char*)&imageInP21[0][0],
             image::ROWS * image::COLS);
  file::read(FILE_PATH_OUT_P2_2, (char*)&imageInP22[0][0],
             image::ROWS * image::COLS);
  file::read(FILE_PATH_OUT_P2_3, (char*)&imageInP23[0][0],
             image::ROWS * image::COLS);

  // Buffers for holding output image data
  unsigned char imageOut1[image::ROWS][image::COLS];
  unsigned char imageOutP21[image::ROWS][image::COLS];
  unsigned char imageOutP22[image::ROWS][image::COLS];
  unsigned char imageOutP23[image::ROWS][image::COLS];

  // Generate histogram for input image
  image::histogram(&imageIn[0][0], &imageOut1[0][0], image::ROWS, image::COLS);
  // Generate histogram for "Programming 2" question image 1
  image::histogram(&imageInP21[0][0], &imageOutP21[0][0], image::ROWS,
                   image::COLS);
  // Generate histogram for "Programming 2" question image 2
  image::histogram(&imageInP22[0][0], &imageOutP22[0][0], image::ROWS,
                   image::COLS);
  // Generate histogram for "Programming 2" question image 3
  image::histogram(&imageInP23[0][0], &imageOutP23[0][0], image::ROWS,
                   image::COLS);

  // // Write outputs to files
  file::write(FILE_PATH_OUT_P3, (char*)&imageOut1[0][0],
              image::ROWS * image::COLS);
  file::write(FILE_PATH_OUT_P3_P2_1, (char*)&imageOutP21[0][0],
              image::ROWS * image::COLS);
  file::write(FILE_PATH_OUT_P3_P2_2, (char*)&imageOutP22[0][0],
              image::ROWS * image::COLS);
  file::write(FILE_PATH_OUT_P3_P2_3, (char*)&imageOutP23[0][0],
              image::ROWS * image::COLS);
}

////////////////////////////////////////////////////////////////////////////////
// MAIN
////////////////////////////////////////////////////////////////////////////////

/**
 * Executes the main program.
 *
 * @param argc Number of command line arguments that were passed
 * @param argv Array containing all arguments that were passed
 *
 */
int main(int argc, char* argv[]) {
  std::cout << "CS 425 - Fall 2019 - Assignment 1" << std::endl;
  std::cout << "Author: Daniel Shevtsov (SID: 200351253)" << std::endl;
  std::cout << "---" << std::endl << std::endl;

  // Buffer for holding input image data
  unsigned char imageIn[image::ROWS][image::COLS];

  try {
    // Read input image to pass to each program
    file::read(FILE_PATH_IN, (char*)&imageIn[0][0], image::ROWS * image::COLS);

    // Run each program with the input image
    program1(imageIn);
    program2(imageIn);
    program3(imageIn);
  } catch (const char* e) {
    std::cout << "Encountered exception:" << std::endl;
    std::cout << "  " << e << std::endl;
    std::cout << "Exiting ..." << std::endl;
    exit(1);
  }

  std::cout << "Finished successfully. Exiting ..." << std::endl;
  exit(0);
}
