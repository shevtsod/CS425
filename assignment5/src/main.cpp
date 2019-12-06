#include <iostream>

#include "file/file.hpp"
#include "image/image.hpp"

////////////////////////////////////////////////////////////////////////////////
// PROGRAM
////////////////////////////////////////////////////////////////////////////////

/**
 * Runs program for "Programming Question" in Assignment 5.
 *
 * Problem statement:
 *   Implement the Fast Fourier Transform (FFT) algorithm that was taught in the
 *   lectures. Given the input images "square256.raw" and "car.raw", generate
 *   the spectra of each as greyscale images.
 */
void program() {
  std::cout << "Running \"Programming Question\" ..." << std::endl;

  // File paths
  const char* FILE_PATH_SQUARE_IN = "./in/square256.raw";
  const char* FILE_PATH_CAR_IN = "./in/car.raw";

  const char* FILE_PATH_SQUARE_OUT = "./out/square256.raw";
  const char* FILE_PATH_CAR_OUT = "./out/car.raw";

  // Image dimensions
  const int ROWS = 256;
  const int COLS = 256;

  // Buffers for holding image data
  unsigned char imageSquareIn[ROWS][COLS];
  unsigned char imageCarIn[ROWS][COLS];
  unsigned char imageSquareOut[ROWS][COLS];
  unsigned char imageCarOut[ROWS][COLS];

  // Read input files into buffers
  file::read(FILE_PATH_SQUARE_IN, (char*)&imageSquareIn[0][0], ROWS * COLS);
  file::read(FILE_PATH_CAR_IN, (char*)&imageCarIn[0][0], ROWS * COLS);

  // Write output buffers to files
  file::write(FILE_PATH_SQUARE_OUT, (char*)&imageSquareOut[0][0], ROWS * COLS);
  file::write(FILE_PATH_CAR_OUT, (char*)&imageCarOut[0][0], ROWS * COLS);
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
  std::cout << "CS 425 - Fall 2019 - Assignment 5" << std::endl
            << "Author: Daniel Shevtsov (SID: 200351253)" << std::endl
            << "---" << std::endl
            << std::endl;

  try {
    // Run all programs
    program();

    std::cout << "Finished successfully. Exiting ..." << std::endl;

    exit(0);
  } catch (const char* e) {
    std::cout << "Encountered unhandled exception:" << std::endl
              << "  " << e << std::endl
              << "Exiting ..." << std::endl;

    exit(1);
  }
}
