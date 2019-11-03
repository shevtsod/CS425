#include <iostream>

#include "image/image.hpp"

#include "file/file.hpp"
#include "image/filter.hpp"
#include "util/util.hpp"

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
  const char* FILE_PATH_OUT_1 = "./out/p1_building_horz.raw";
  const char* FILE_PATH_OUT_2 = "./out/p1_building_vert.raw";
  const char* FILE_PATH_OUT_3 = "./out/p1_building_gradient.raw";
  const char* FILE_PATH_OUT_4 = "./out/p1_building_thres_gradient.raw";

  // Image dimensions
  const int ROWS = 420;
  const int COLS = 560;

  // Buffers for holding image data
  unsigned char imageIn[ROWS][COLS];
  unsigned char imageSobelHorz[ROWS][COLS];
  unsigned char imageSobelVert[ROWS][COLS];
  unsigned char imageGradient[ROWS][COLS];
  unsigned char imageThresGradient[ROWS][COLS];

  // Buffers for holding image filter masks
  const double FILTER_SOBEL_HORZ[image::MASK_SIZE][image::MASK_SIZE] = {
      -1, -2, -1, 0, 0, 0, 1, 2, 1};
  const double FILTER_SOBEL_VERT[image::MASK_SIZE][image::MASK_SIZE] = {
      -1, 0, 1, -2, 0, 2, -1, 0, 1};

  // Read input file into buffer
  file::read(FILE_PATH_IN, (char*)&imageIn[0][0], ROWS * COLS);

  // Compute horizontal edge image using Sobel filter
  image::applyLinearFilter(&imageIn[0][0], FILTER_SOBEL_HORZ,
                           &imageSobelHorz[0][0], ROWS, COLS);

  // Compute vertical edge image using Sobel filter
  image::applyLinearFilter(&imageIn[0][0], FILTER_SOBEL_VERT,
                           &imageSobelVert[0][0], ROWS, COLS);

  // Compute gradient image using magnitude of horizontal and vertical Sobel
  // filtered images
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      imageGradient[i][j] =
          util::magnitude(imageSobelHorz[i][j], imageSobelVert[i][j]);
    }
  }

  // Apply threshold to gradient using Te = 128
  image::applyThreshold(&imageGradient[0][0], &imageThresGradient[0][0], ROWS,
                        COLS, image::LEVEL_BLACK, image::LEVEL_WHITE, 128);

  // Write output buffers to files
  file::write(FILE_PATH_OUT_1, (char*)&imageSobelHorz[0][0], ROWS * COLS);
  file::write(FILE_PATH_OUT_2, (char*)&imageSobelVert[0][0], ROWS * COLS);
  file::write(FILE_PATH_OUT_3, (char*)&imageGradient[0][0], ROWS * COLS);
  file::write(FILE_PATH_OUT_4, (char*)&imageThresGradient[0][0], ROWS * COLS);
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
  const char* FILE_PATH_OUT_1 = "./out/p2_moon_w_0.5.raw";
  const char* FILE_PATH_OUT_2 = "./out/p2_moon_w_1.0.raw";
  const char* FILE_PATH_OUT_3 = "./out/p2_moon_w_2.0.raw";

  // Image dimensions
  const int ROWS = 528;
  const int COLS = 464;

  // Buffers for holding image data
  unsigned char imageIn[ROWS][COLS];
  unsigned char imageOutW05[ROWS][COLS];
  unsigned char imageOutW1[ROWS][COLS];
  unsigned char imageOutW2[ROWS][COLS];

  // Read input file into buffer
  file::read(FILE_PATH_IN, (char*)&imageIn[0][0], ROWS * COLS);

  // Apply Laplace sharpening with w = 0.5
  image::applyLaplaceSharpening(&imageIn[0][0], &imageOutW05[0][0], ROWS, COLS,
                                0.5);
  // Apply Laplace sharpening with w = 1.0
  image::applyLaplaceSharpening(&imageIn[0][0], &imageOutW1[0][0], ROWS, COLS,
                                1.0);
  // Apply Laplace sharpening with w = 2.0
  image::applyLaplaceSharpening(&imageIn[0][0], &imageOutW2[0][0], ROWS, COLS,
                                2.0);

  // Write output buffers to files
  file::write(FILE_PATH_OUT_1, (char*)&imageOutW05[0][0], ROWS * COLS);
  file::write(FILE_PATH_OUT_2, (char*)&imageOutW1[0][0], ROWS * COLS);
  file::write(FILE_PATH_OUT_3, (char*)&imageOutW2[0][0], ROWS * COLS);
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
