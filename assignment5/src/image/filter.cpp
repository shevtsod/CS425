#include "filter.hpp"

#include "../util/util.hpp"
#include "image.hpp"

namespace image {

/**
 * Produces a new image by scanning through the given image with the given mask
 * and outputs the result to the destination buffer. The mask is of size
 * MASK_SIZE x MASK_SIZE.
 *
 * @param SRC  Buffer containing original image
 * @param MASK Mask or filter to scan through original image with
 * @param dest Destination buffer for filtered image
 * @param ROWS Number of rows in original image
 * @param COLS Number of columns in original image
 */
void applyLinearFilter(const unsigned char* SRC,
                       const double MASK[MASK_SIZE][MASK_SIZE],
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
      for (int k = -MASK_SIZE_HALF; k <= MASK_SIZE_HALF; k++) {
        for (int l = -MASK_SIZE_HALF; l <= MASK_SIZE_HALF; l++) {
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
          double weight = MASK[k + MASK_SIZE_HALF][l + MASK_SIZE_HALF];

          // Update the sum with this pixel and its weight
          sum += pixel * weight;

          // Increment count of pixels inside the bounds of the mask
          count++;
        }
      }

      // Calculate weighted sum and re-normalize based on number of pixels that
      // were out of bounds
      int output = sum * MASK_SIZE * MASK_SIZE / count;

      // Clamp output value if out of bounds
      if (output < 0) {
        output = 0;
      }

      if (output > image::LEVEL_WHITE) {
        output = image::LEVEL_WHITE;
      }

      // Output the weighted sum into the output image at the same pixel
      dest[COLS * i + j] = output;
    }
  }
}

/**
 * Produces a new image by scanning through the given image and outputs the
 * result to the destination buffer. The mask used is of size MASK_SIZE x
 * MASK_SIZE.
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
      unsigned char maskPixels[MASK_SIZE * MASK_SIZE];
      // Count of pixels inside the bounds of the mask
      int count = 0;

      // Iterate through the mask
      for (int k = -MASK_SIZE_HALF; k <= MASK_SIZE_HALF; k++) {
        for (int l = -MASK_SIZE_HALF; l <= MASK_SIZE_HALF; l++) {
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
          maskPixels[count] = pixel;

          // Increment count of pixels inside the bounds of the mask
          count++;
        }
      }

      // Sort the buffer of pixels inside the mask to get the median value
      unsigned char sortedMaskPixels[MASK_SIZE * MASK_SIZE];
      util::insertionSort(maskPixels, sortedMaskPixels, count);

      // Output the median into the output image at the same pixel
      dest[i * COLS + j] = util::median(sortedMaskPixels, count);
    }
  }
}

/**
 * Produces a new image containing the gradient of the given image and outputs
 * the result to the destination buffer.
 *
 * @param SRC  Buffer containing original image
 * @param dest Destination buffer for filtered image
 * @param ROWS Number of rows in original image
 * @param COLS Number of columns in original image
 */
void genGradient(const unsigned char* SRC,
                 unsigned char* dest,
                 const int ROWS,
                 const int COLS) {
  // Filter mask for gradient
  const double MASK_GRADIENT[image::MASK_SIZE] = {-0.5, 0, 0.5};

  // Iterate through the image
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      // Sum of pixels for horizontal partial derivative approximation
      double sumX = 0;
      // Count of pixels for horizontal partial derivative approximation
      int countX = 0;

      // Iterate through the mask for the current pixel's horizontal neighbours
      // and calculate horizontal partial derivative approximation
      for (int k = -MASK_SIZE_HALF; k <= MASK_SIZE_HALF; k++) {
        // Ensure that the pixel is within bounds
        if ((j + k) < 0 || (j + k) >= COLS) {
          continue;
        }

        // Add current pixel and weight to weighted sum
        sumX += SRC[COLS * i + j + k] * MASK_GRADIENT[MASK_SIZE_HALF + k];
        countX++;
      }

      // Re-normalize based on number of pixels that were out of bounds
      sumX *= MASK_SIZE / countX;

      // Sum of pixels for vertical partial derivative approximation
      double sumY = 0;
      // Count of pixels for vertical partial derivative approximation
      int countY = 0;

      // Iterate through the mask for the current pixel's vertical neighbours
      for (int k = -MASK_SIZE_HALF; k <= MASK_SIZE_HALF; k++) {
        // Ensure that the pixel is within bounds
        if ((i + k) < 0 || (i + k) >= ROWS) {
          continue;
        }

        // Add current pixel and weight to weighted sum
        sumY += SRC[COLS * (i + k) + j] * MASK_GRADIENT[MASK_SIZE_HALF + k];
        countY++;
      }

      // Re-normalize based on number of pixels that were out of bounds
      sumY *= MASK_SIZE / countY;

      // Calculate magnitude using horizontal (x) and vertical (y) partial
      // derivatives
      int output = util::magnitude(sumX, sumY);

      // Clamp output value if out of bounds
      if (output < 0) {
        output = 0;
      }

      if (output > image::LEVEL_WHITE) {
        output = image::LEVEL_WHITE;
      }

      // Output the weighted sum into the output image at the same pixel
      dest[COLS * i + j] = output;
    }
  }
}

/**
 * Produces a new image that is sharpened using the Laplace filter. The given
 * weight controls the strength of sharpening.
 *
 * @param SRC    Buffer containing original image
 * @param dest   Destination buffer for filtered image
 * @param ROWS   Number of rows in original image
 * @param COLS   Number of columns in original image
 * @param WEIGHT Strength of sharpening, a higher value produces a sharper image
 */
void applyLaplaceSharpening(const unsigned char* SRC,
                            unsigned char* dest,
                            const int ROWS,
                            const int COLS,
                            const double WEIGHT) {
  // Filter mask for Laplacian filter
  const double MASK_LAPLACIAN[image::MASK_SIZE][image::MASK_SIZE] = {
      0, 1, 0, 1, -4, 1, 0, 1, 0};
  // Buffer to hold Laplacian filter of image
  int laplacian[ROWS][COLS];

  // Iterate through the image to generate Laplacian buffer
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      // Sum of pixels inside the bounds of the mask
      double sum = 0;
      // Count of pixels inside the bounds of the mask
      int count = 0;

      // Iterate through the mask
      for (int k = -MASK_SIZE_HALF; k <= MASK_SIZE_HALF; k++) {
        for (int l = -MASK_SIZE_HALF; l <= MASK_SIZE_HALF; l++) {
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
              MASK_LAPLACIAN[k + MASK_SIZE_HALF][l + MASK_SIZE_HALF];

          // Update the sum with this pixel and its weight
          sum += pixel * weight;

          // Increment count of pixels inside the bounds of the mask
          count++;
        }
      }

      // Calculate weighted sum and re-normalize based on number of pixels that
      // were out of bounds
      int output = sum * MASK_SIZE * MASK_SIZE / count;

      // Output the weighted sum into the output image at the same pixel
      laplacian[i][j] = output;
    }
  }

  // Sharpen image using Laplacian following the formula:
  //   I' = I - w * (Hl * I)
  // Where I is the original image, w is the given weight, and (Hl * I) is the
  // image with the Laplacian filter applied to it.
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      int output = SRC[COLS * i + j] - WEIGHT * laplacian[i][j];

      // Clamp output value if out of bounds
      if (output < 0) {
        output = 0;
      }

      if (output > image::LEVEL_WHITE) {
        output = image::LEVEL_WHITE;
      }

      dest[COLS * i + j] = output;
    }
  }
}

}  // namespace image
