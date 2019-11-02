#include "filter.hpp"

#include "../util/util.hpp"

namespace image {

/**
 * Produces a new image by scanning through the given image with the given mask
 * and outputs the result to the destination buffer. The mask is of size
 * MASK_DIMENSION x MASK_DIMENSION.
 *
 * @param SRC  Buffer containing original image
 * @param MASK Mask or filter to scan through original image with
 * @param dest Destination buffer for filtered image
 * @param ROWS Number of rows in original image
 * @param COLS Number of columns in original image
 */
void applyLinearFilter(const unsigned char* SRC,
                       const double MASK[MASK_DIMENSION][MASK_DIMENSION],
                       unsigned char* dest,
                       const int ROWS,
                       const int COLS) {
  // Iterate through the image
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      // Sum of pixels inside the bounds of the mask
      double sum = 0;
      // Count of pixels inside the bounds of the mask
      int count = 0;

      // Iterate through the mask
      for (int k = -MASK_HALF_DIMENSION; k <= MASK_HALF_DIMENSION; k++) {
        for (int l = -MASK_HALF_DIMENSION; l <= MASK_HALF_DIMENSION; l++) {
          // Ensure that the current pixel is not out of bounds
          if ((i + k) < 0 || (i + k) >= ROWS) {
            continue;
          }

          if ((j + l) < 0 || (j + l) >= COLS) {
            continue;
          }

          // Using row major order indexing
          unsigned char pixel = SRC[COLS * (i + k) + j + l];

          // The weight of the mask at this pixel
          double weight =
              MASK[k + MASK_HALF_DIMENSION][l + MASK_HALF_DIMENSION];

          // Update the sum with this pixel and its weight
          sum += pixel * weight;

          // Increment count of pixels inside the bounds of the mask
          count++;
        }
      }

      // Calculate weighted sum and re-normalize based on number of pixels that
      // were out of bounds
      unsigned char output =
          (unsigned char)((int)(sum * MASK_DIMENSION * MASK_DIMENSION / count));

      // Output the weighted sum into the output image at the same pixel
      dest[COLS * i + j] = output;
    }
  }
}

/**
 * Produces a new image by scanning through the given image and outputs the
 * result to the destination buffer. The mask used is of size MASK_DIMENSION x
 * MASK_DIMENSION.
 *
 * @param SRC  Buffer containing original image
 * @param dest Destination buffer for filtered image
 * @param ROWS Number of rows in original image
 * @param COLS Number of columns in original image
 */
void applyMedianFilter(const unsigned char* SRC,
                       unsigned char* dest,
                       const int ROWS,
                       const int COLS) {
  // Iterate through the image
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      // Buffer of pixels inside the bounds of the mask
      unsigned char MASK_PIXELS[MASK_DIMENSION * MASK_DIMENSION];
      // Count of pixels inside the bounds of the mask
      int count = 0;

      // Iterate through the mask
      for (int k = -MASK_HALF_DIMENSION; k <= MASK_HALF_DIMENSION; k++) {
        for (int l = -MASK_HALF_DIMENSION; l <= MASK_HALF_DIMENSION; l++) {
          // Ensure that the current pixel is not out of bounds
          if ((i + k) < 0 || (i + k) >= ROWS) {
            continue;
          }

          if ((j + l) < 0 || (j + l) >= COLS) {
            continue;
          }

          // Using row major order indexing
          unsigned char pixel = SRC[COLS * (i + k) + j + l];

          // Add this pixel to the mask pixels buffer
          MASK_PIXELS[count] = pixel;

          // Increment count of pixels inside the bounds of the mask
          count++;
        }
      }

      // Sort the buffer of pixels inside the mask to get the median value
      unsigned char SORTED_MASK_PIXELS[MASK_DIMENSION * MASK_DIMENSION];

      util::insertionSort(MASK_PIXELS, SORTED_MASK_PIXELS, count);

      // Get the median (middle value)
      const int MEDIAN_INDEX = (double)(count - 1) / 2;
      unsigned char output = SORTED_MASK_PIXELS[MEDIAN_INDEX];

      // Output the median into the output image at the same pixel
      dest[i * COLS + j] = output;
    }
  }
}

}  // namespace image
