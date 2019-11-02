#include <iostream>

#include "file/file.hpp"
#include "image/filter.hpp"
#include "image/histogram.hpp"

////////////////////////////////////////////////////////////////////////////////
// PROGRAM 1
////////////////////////////////////////////////////////////////////////////////

/**
 * Runs program for "Programming 1" question in Assignment 3.
 *
 * Problem statement:
 *   Implement the 3x3 Sobel edge operator. Given the input file
 *   "building.raw", compute the following:
 *
 *   - Horizontal edge image
 *   - Vertical edge image
 *   - Gradient image
 *   - Thresholded gradient image using threshold Te = 128.
 */
void program1() {
  std::cout << "Running \"Programming 1\" ..." << std::endl;

  // File paths
  const char* FILE_PATH_IN = "./in/building.raw";
  const char* FILE_PATH_OUT_1 = "./out/p1_building_horiz.raw";
  const char* FILE_PATH_OUT_2 = "./out/p1_building_vert.raw";
  const char* FILE_PATH_OUT_3 = "./out/p1_building_gradient.raw";
  const char* FILE_PATH_OUT_4 = "./out/p1_building_thres_gradient.raw";

  // Image dimensions
  const int ROWS = 420;
  const int COLS = 560;

  // Buffers for holding image data
  unsigned char imageIn[ROWS][COLS];
  unsigned char imageOut1[ROWS][COLS];
  unsigned char imageOut2[ROWS][COLS];
  unsigned char imageOut3[ROWS][COLS];
  unsigned char imageOut4[ROWS][COLS];

  // Read input file into buffer
  file::read(FILE_PATH_IN, (char*)&imageIn[0][0], ROWS * COLS);

  // Write output buffers to files
  file::write(FILE_PATH_OUT_1, (char*)&imageOut1[0][0], ROWS * COLS);
  file::write(FILE_PATH_OUT_2, (char*)&imageOut1[0][0], ROWS * COLS);
  file::write(FILE_PATH_OUT_3, (char*)&imageOut1[0][0], ROWS * COLS);
  file::write(FILE_PATH_OUT_4, (char*)&imageOut1[0][0], ROWS * COLS);
}

////////////////////////////////////////////////////////////////////////////////
// PROGRAM 2
////////////////////////////////////////////////////////////////////////////////

/**
 * Runs program for "Programming 2" question in Assignment 2.
 *
 * Problem statement:
 *   Implement the 3x3 Laplacian sharpening filter. Given the input file
 *   "moon.raw", sharpen the image with different values of w.
 */
void program2() {
  std::cout << "Running \"Programming 2\" ..." << std::endl;

  // File paths
  const char* FILE_PATH_IN = "./in/moon.raw";
  const char* FILE_PATH_OUT_1 = "./out/p2_moon_w_1.raw";
  const char* FILE_PATH_OUT_2 = "./out/p2_moon_w_2.raw";
  const char* FILE_PATH_OUT_3 = "./out/p2_moon_w_4.raw";

  // Image dimensions
  const int ROWS = 528;
  const int COLS = 464;

  // Buffers for holding image data
  unsigned char imageIn[ROWS][COLS];
  unsigned char imageOut1[ROWS][COLS];
  unsigned char imageOut2[ROWS][COLS];
  unsigned char imageOut3[ROWS][COLS];

  // Read input file into buffer
  file::read(FILE_PATH_IN, (char*)&imageIn[0][0], ROWS * COLS);

  // Write output buffers to files
  file::write(FILE_PATH_OUT_1, (char*)&imageOut1[0][0], ROWS * COLS);
  file::write(FILE_PATH_OUT_2, (char*)&imageOut2[0][0], ROWS * COLS);
  file::write(FILE_PATH_OUT_3, (char*)&imageOut2[0][0], ROWS * COLS);
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
  std::cout << "CS 425 - Fall 2019 - Assignment 3" << std::endl
            << "Author: Daniel Shevtsov (SID: 200351253)" << std::endl
            << "---" << std::endl
            << std::endl;

  try {
    // Run all programs
    program1();
    program2();

    std::cout << "Finished successfully. Exiting ..." << std::endl;

    exit(0);
  } catch (const char* e) {
    std::cout << "Encountered unhandled exception:" << std::endl
              << "  " << e << std::endl
              << "Exiting ..." << std::endl;

    exit(1);
  }
}
