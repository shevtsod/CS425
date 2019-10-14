#include "histogram.h"

#include "image.h"

namespace image {

/**
 * Produces a histogram of the given image buffer into the destination buffer.
 * The histogram is a single-dimensional array of size LEVELS where the value
 * at each level is the frequency of pixels of that level.
 *
 * @param SRC  Buffer containing original image
 * @param dest Destination buffer for histogram
 * @param ROWS Number of rows in original image
 * @param COLS Number of columns in original image
 */
void genHistogram(const unsigned char* SRC,
                  int dest[],
                  const int ROWS,
                  const int COLS) {
  // Initialize histogram buffer
  for (int i = 0; i < LEVELS; i++) {
    dest[i] = 0;
  }

  // Iterate through source image buffer and count grey level frequencies
  for (int i = 0; i < ROWS * COLS; i++) {
    // Temporarily store value of current character (pixel)
    unsigned char character = SRC[i];

    // Increment frequency of this character in counts buffer
    dest[character]++;
  }
}

/**
 * Produces a cumulative histogram of the given histogram buffer into the
 * destination buffer. The cumulative histogram is a single-dimensional array of
 * size LEVELS where the value at each level is the sum of frequencies of pixels
 * up to that level.
 *
 * @param SRC  Buffer containing histogram
 * @param dest Destination buffer for cumulative histogram
 */
void genCumulativeHistogram(const int SRC[], int dest[]) {
  // Track current total of frequencies
  int total = 0;

  // Iterate through the histogram
  for (int i = 0; i < LEVELS; i++) {
    // Increment total
    total += SRC[i];

    // Enter the current total into the respective index in the cumulative
    // histogram
    dest[i] = total;
  }
}

/**
 * Produces a new histogram normalized with a scaling factor from the given
 * histogram buffer into the destination buffer. The histogram is a
 * single-dimensional array of size LEVELS where the value at each level is the
 * frequency of pixels of that level.
 *
 * @param SRC    Buffer containing histogram
 * @param dest   Destination buffer for normalized histogram
 * @param FACTOR Normalization factor
 */
void genNormalizedHistogram(const int SRC[], int dest[], const double FACTOR) {
  // Iterate through the original histogram and scale each value into the
  // destination buffer
  for (int i = 0; i < LEVELS; i++) {
    dest[i] = SRC[i] * FACTOR;
  }
}

/**
 * Produces a new image buffer from a given histogram of size LEVELS.
 * The destination buffer must have the dimensions LEVELS x LEVELS. The
 * histogram is scaled to fit the entire available image size vertically. Uses
 * grey levels defined in image::LEVEL_WHITE and image::LEVEL_BLACK for
 * background and foreground colours, respectively.
 *
 * @param SRC  Buffer containing histogram
 * @param dest Destination buffer for histogram image
 */
void genHistogramImage(const int SRC[], unsigned char* dest) {
  // Scaled histogram buffer
  int scaledSrc[LEVELS];
  // Cursor for destination image buffer
  unsigned char* ptrDest = dest;
  // Track maximum frequency
  int maxCount = 0;

  // Iterate through the histogram buffer to find the maximum value
  for (int i = 0; i < LEVELS; i++) {
    // Get the count at this level
    int count = SRC[i];

    if (count > maxCount) {
      maxCount = count;
    }
  }

  // Normalize the histogram buffer from range [0, maxCount] to [0, 255]
  genNormalizedHistogram(SRC, &scaledSrc[0], (double)(LEVELS - 1) / maxCount);

  // Current row and column in destination image
  int row = 0;
  int col = 0;

  // Convert character counts to histogram in destination image buffer
  for (int i = 0; i < LEVELS * LEVELS; i++) {
    // Use foreground colour if count for current column is equal to or higher
    // than current row value. Otherwise, use background colour.
    if (scaledSrc[col] != 0 && scaledSrc[col] >= (LEVELS - 1 - row)) {
      *ptrDest = LEVEL_BLACK;
    } else {
      *ptrDest = LEVEL_WHITE;
    }

    // Increment destination image buffer cursor
    ptrDest++;

    // Increment column in destination image
    col++;

    // Increment row if reached end of current row
    if (col >= LEVELS) {
      row++;
      col = 0;
    }
  }
}

/**
 * Produces a new image by equalizing the histogram at the source buffer to the
 * Equalizes a discrete histogram at the source buffer to the destination
 * buffer. The histogram is a single-dimensional array of size LEVELS where the
 * value at each level is the frequency of pixels of that level.
 *
 * @param SRC  Buffer containing original image
 * @param dest Destination buffer for image with equalized histogram
 * @param ROWS Number of rows in original image
 * @param COLS Number of columns in original image
 */
void genEqualizedHistogramImage(const unsigned char* SRC,
                                unsigned char* dest,
                                const int ROWS,
                                const int COLS) {
  // Buffer for holding histogram
  int h[LEVELS];
  // Buffer for holding cumulative histogram
  int H[LEVELS];

  // Scaling factor is defined as S = (K - 1) / (M * N)
  double S = (double)(LEVELS - 1) / (ROWS * COLS);

  // Computer histogram for original image
  genHistogram(SRC, &h[0], ROWS, COLS);

  // Compute cumulative histogram from the given histogram
  genCumulativeHistogram(&h[0], &H[0]);

  // Normalize cumulative histogram with scaling factor
  genNormalizedHistogram(&H[0], &H[0], S);

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      // Using row major order indexing
      unsigned char pixel = SRC[LEVELS * i + j];

      dest[LEVELS * i + j] = H[pixel];
    }
  }
}

}  // namespace image
