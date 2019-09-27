#include <fstream>
#include <iostream>

#include "file.h"
#include "image.h"

////////////////////////////////////////////////////////////////////////////////
// CONSTANTS
////////////////////////////////////////////////////////////////////////////////

// File paths

const char* FILE_PATH_IN = "./in/rose.raw";

const char* FILE_PATH_OUT_P1_1 = "./out/p1-rose1.raw";
const char* FILE_PATH_OUT_P1_2 = "./out/p1-rose2.raw";
const char* FILE_PATH_OUT_P1_3 = "./out/p1-rose3.raw";

const char* FILE_PATH_OUT_P2_1 = "./out/p2-rose1.raw";
const char* FILE_PATH_OUT_P2_2 = "./out/p2-rose2.raw";
const char* FILE_PATH_OUT_P2_3 = "./out/p2-rose3.raw";

const char* FILE_PATH_OUT_P3 = "./out/p3-histogram-rose.raw";
const char* FILE_PATH_OUT_P3_P2_1 = "./out/p3-histogram-rose-p2-1.raw";
const char* FILE_PATH_OUT_P3_P2_2 = "./out/p3-histogram-rose-p2-2.raw";
const char* FILE_PATH_OUT_P3_P2_3 = "./out/p3-histogram-rose-p2-3.raw";

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

  // Write outputs to files
  file::write(FILE_PATH_OUT_P1_1, (char*)&imageIn[0][0],
              image::ROWS * image::COLS / 2);
  file::write(FILE_PATH_OUT_P1_2, (char*)&imageIn[0][0],
              image::ROWS * image::COLS / 4);
  file::write(FILE_PATH_OUT_P1_3, (char*)&imageIn[0][0],
              image::ROWS * image::COLS / 8);

  // Q: What are the effects of reducing the size of an image?
  // A: The smaller the image becomes, the more detail is lost and the harder
  //    it becomes to discern the object that is being depicted.
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

  // Write outputs to files
  file::write(FILE_PATH_OUT_P2_1, (char*)&imageIn[0][0],
              image::ROWS * image::COLS);
  file::write(FILE_PATH_OUT_P2_2, (char*)&imageIn[0][0],
              image::ROWS * image::COLS);
  file::write(FILE_PATH_OUT_P2_3, (char*)&imageIn[0][0],
              image::ROWS * image::COLS);

  // Q: What are the effects of reducing the number of bits of each pixel?
  // A: Reducing the number of bits per pixel reduces the number of grey levels
  //    in a greyscale image. As a result, gradients start appearing as "bands"
  //    rather than a smooth transition between two grey levels.
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

  // Write histogram to file
  file::write(FILE_PATH_OUT_P3, (char*)&imageIn[0][0],
              image::ROWS * image::COLS);

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

  // Write histograms for "Programming 2" question images to files
  file::write(FILE_PATH_OUT_P3_P2_1, (char*)&imageInP21[0][0],
              image::ROWS * image::COLS);
  file::write(FILE_PATH_OUT_P3_P2_2, (char*)&imageInP22[0][0],
              image::ROWS * image::COLS);
  file::write(FILE_PATH_OUT_P3_P2_3, (char*)&imageInP23[0][0],
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
  } catch (std::string e) {
    std::cout << "Encountered exception:" << std::endl;
    std::cout << "  " << e << std::endl;
    std::cout << "Exiting ..." << std::endl;
    exit(1);
  }

  std::cout << "Finished successfully. Exiting ..." << std::endl;
  exit(0);
}
