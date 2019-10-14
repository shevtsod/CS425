#include <iostream>

#include "file/file.h"
#include "image/filter.h"
#include "image/histogram.h"

////////////////////////////////////////////////////////////////////////////////
// PROGRAM 1
////////////////////////////////////////////////////////////////////////////////

/**
 * Runs program for "Programming 1" question in Assignment 2.
 *
 * Problem statement:
 *   Apply the histogram equalization algorithm discussed in class to the input
 *   image "ct.raw".
 */
void program1() {
  std::cout << "Running \"Programming 1\" ..." << std::endl;

  // File paths
  const char* FILE_PATH_IN = "./in/ct.raw";
  const char* FILE_PATH_OUT = "./out/p1_histogram_ct.raw";

  // Image dimensions
  const int ROWS = 256;
  const int COLS = 256;

  // Buffers for holding image data
  unsigned char imageIn[ROWS][COLS];
  unsigned char imageOut[ROWS][COLS];

  // Read input file into buffer
  file::read(FILE_PATH_IN, (char*)&imageIn[0][0], ROWS * COLS);

  // Compute the equalized histogram
  image::genEqualizedHistogramImage(&imageIn[0][0], &imageOut[0][0], ROWS,
                                    COLS);

  // Write output buffers to files
  file::write(FILE_PATH_OUT, (char*)&imageOut[0][0], ROWS * COLS);
}

////////////////////////////////////////////////////////////////////////////////
// PROGRAM 2
////////////////////////////////////////////////////////////////////////////////

/**
 * Runs program for "Programming 2" question in Assignment 2.
 *
 * Problem statement:
 *   Implement the following averaging filters for smoothing:
 *
 *            |1 1 1|
 *   H1 = 1/9 |1 1 1|
 *            |1 1 1|
 *
 *        |0.075 0.125 0.075|
 *   H2 = |0.125 0.200 0.125|
 *        |0.075 0.125 0.075|
 *
 *   Apply the filters to input file "testpattern.raw".
 *   Are there visible visual differences between the results of the two
 *   filters?
 */
void program2() {
  std::cout << "Running \"Programming 2\" ..." << std::endl;

  // File paths
  const char* FILE_PATH_IN = "./in/testpattern.raw";
  const char* FILE_PATH_OUT_1 = "./out/p2_testpattern_h1.raw";
  const char* FILE_PATH_OUT_2 = "./out/p2_testpattern_h2.raw";

  // Image dimensions
  const int ROWS = 500;
  const int COLS = 500;

  // Buffers for holding image data
  unsigned char imageIn[ROWS][COLS];
  unsigned char imageOut1[ROWS][COLS];
  unsigned char imageOut2[ROWS][COLS];
  double H1[image::MASK_DIMENSION][image::MASK_DIMENSION] = {
      1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9,
      1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9};
  double H2[image::MASK_DIMENSION][image::MASK_DIMENSION] = {
      0.075, 0.125, 0.075, 0.125, 0.200, 0.125, 0.075, 0.125, 0.075};

  // Read input file into buffer
  file::read(FILE_PATH_IN, (char*)&imageIn[0][0], ROWS * COLS);

  // Apply averaging filter H1 into first output buffer
  image::applyLinearFilter(&imageIn[0][0], H1, &imageOut1[0][0], ROWS, COLS);

  // Apply averaging filter H2 into second output buffer
  image::applyLinearFilter(&imageIn[0][0], H2, &imageOut2[0][0], ROWS, COLS);

  // Write output buffers to files
  file::write(FILE_PATH_OUT_1, (char*)&imageOut1[0][0], ROWS * COLS);
  file::write(FILE_PATH_OUT_2, (char*)&imageOut2[0][0], ROWS * COLS);

  // Q: Are there visible visual differences between the results of the two
  //    filters?
  // A: Both filters smooth or blur the image, but there are slight visible
  //    differences. In particular, small dots and sharp edges in the original
  //    image appear as boxes when filter H1 is applied, but they appear rounder
  //    when filter H2 is applied.
}

////////////////////////////////////////////////////////////////////////////////
// PROGRAM 3
////////////////////////////////////////////////////////////////////////////////

/**
 * Runs program for "Programming 3" question in Assignment 2.
 *
 * Problem statement:
 *   Apply the 3x3 median filter to the noisy input image "circuit.raw".
 */
void program3() {
  std::cout << "Running \"Programming 3\" ..." << std::endl;

  // File paths
  const char* FILE_PATH_IN = "./in/circuit.raw";
  const char* FILE_PATH_OUT = "./out/p3_circuit.raw";

  // Image dimensions
  const int ROWS = 440;
  const int COLS = 455;

  // Buffers for holding image data
  unsigned char imageIn[ROWS][COLS];
  unsigned char imageOut[ROWS][COLS];

  // Read input file into buffer
  file::read(FILE_PATH_IN, (char*)&imageIn[0][0], ROWS * COLS);

  // Apply median filter to input image
  image::applyMedianFilter(&imageIn[0][0], &imageOut[0][0], ROWS, COLS);

  // Write output buffers to files
  file::write(FILE_PATH_OUT, (char*)&imageOut[0][0], ROWS * COLS);
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
  std::cout << "CS 425 - Fall 2019 - Assignment 2" << std::endl
            << "Author: Daniel Shevtsov (SID: 200351253)" << std::endl
            << "---" << std::endl
            << std::endl;

  try {
    // Run all programs
    program1();
    program2();
    program3();

    std::cout << "Finished successfully. Exiting ..." << std::endl;

    exit(0);
  } catch (const char* e) {
    std::cout << "Encountered unhandled exception:" << std::endl
              << "  " << e << std::endl
              << "Exiting ..." << std::endl;

    exit(1);
  }
}
