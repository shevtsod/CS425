#include "image.h"

namespace image {

/**
 * Returns a character with the bit at the given position unset.
 * Least significant bit = position 0.
 *
 * @param character Original character
 * @param position Bit position to unset
 * @returns Character with bit at given position unset
 */
unsigned char unsetBit(const unsigned char character, int position) {
  return character & ~(1 << position);
}

/**
 * Returns the average character value given an arbitrary buffer of characters.
 *
 * @param characters Buffer containing characters to average
 * @param size Size of buffer
 * @returns Average character value in buffer
 */
unsigned char average(unsigned char* characters, const unsigned long size) {
  // Handle case of empty buffer
  if (size == 0) {
    return 0;
  }

  unsigned long sum = 0;

  // Get the sum of all character values
  for (int i = 0; i < size; i++) {
    sum += (unsigned long)characters[i];
  }

  // Divide sum by number of elements in buffer
  return sum / size;
}

/**
 * Scales down an image at a source buffer into a destination buffer.
 * The image is scaled down by dividing it into blocks based on the size of the
 * scaling factor and averaging the values of the pixels at each block into the
 * destination buffer.
 *
 * The given scaling factor determines the new scale of the image. For example,
 * a scaling factor of 1 maintains the original size, a factor of 2 halves the
 * image scale, and a factor of 4 produces an image at a quarter of the scale of
 * the original image. The scaling factor must be a power of 2.
 *
 * @param src Buffer containing original image
 * @param dest Destination buffer for downscaled image
 * @param rows Number of rows in original image
 * @param cols Number of columns in original image
 * @param factor Downscaling factor
 */
void downscale(unsigned char* src,
               unsigned char* dest,
               const int rows,
               const int cols,
               const int factor) {
  // Ensure that the scaling factor is a power of 2
  if (factor <= 0 || (factor & (factor - 1) == 0)) {
    throw "ERROR: Scaling factor must be a power of 2!";
  }

  // Dimensions of destination image
  int destRows = rows / factor;
  int destCols = cols / factor;
  // Current column in source image
  int col = 0;
  // Cursor for source buffer
  unsigned char* ptrSrc = src;

  // Divide the source image into blocks based on the destination image size
  for (int i = 0; i < destRows * destCols; i++) {
    // Smaller buffer to hold the block's pixels
    unsigned char block[factor][factor];

    // Populate this block with the corresponding pixels from the source image
    for (int j = 0; j < factor; j++) {
      for (int k = 0; k < factor; k++) {
        // Index element in source buffer using row major order
        block[j][k] = ptrSrc[cols * j + k];
      }
    }

    // Average the values of the pixels at this block into the
    // destination buffer
    dest[i] = image::average(&block[0][0], factor * factor);

    // Increment current column in source image
    col += factor;

    // Check if reached end of current row
    if (col < cols) {
      // If not end of row, shift left one block
      ptrSrc += factor;
    } else {
      // If end of row, shift down one block
      ptrSrc += factor + cols * (factor - 1);

      col = 0;
    }
  }
}

/**
 * Produces an image with a lower bit quantization into the destination buffer.
 * The quantization is reduced by unsetting the N lowest order bits per pixel.
 *
 * @param src Buffer containing original image
 * @param dest Destination buffer for reduced quantization image
 * @param rows Number of rows in original image
 * @param cols Number of columns in original image
 * @param unsetBitCount Number of lowest order bits to unset
 */
void reduceQuantization(unsigned char* src,
                        unsigned char* dest,
                        const int rows,
                        const int cols,
                        const int unsetBitCount) {
  // Ensure that no more bits are unset than are available in a character
  if (unsetBitCount >= sizeof(char) * 8) {
    throw "ERROR: Bit position out of range!";
  }

  // Loop through the entire source image pixel by pixel
  for (int i = 0; i < rows * cols; i++) {
    // Temporarily store value of current character (pixel)
    unsigned char character = src[i];

    // Unset the lowest order N bits from the source image buffer and store in
    // destination image buffer at the same location
    for (int j = 0; j < unsetBitCount; j++) {
      character = image::unsetBit(character, j);
    }

    // Set character with unset bits
    dest[i] = character;
  }
}

/**
 * Produces a histogram of the given image buffer into the destination buffer.
 * The histogram has the same dimensions as the source image and is scaled so
 * as to fit the entire available image size vertically.
 * Uses grey levels defined in image::BACKGROUND and image::FOREGROUND for
 * background and foreground colours, respectively.
 *
 * @param src Buffer containing original image
 * @param dest Destination buffer for histogram
 * @param rows Number of rows in original image
 * @param cols Number of columns in original image
 */
void histogram(unsigned char* src,
               unsigned char* dest,
               const int rows,
               const int cols) {
  // Buffer to hold grey level counts
  int counts[image::LEVELS];
  // Track maximum achieved count
  int maxCount = 0;
  // Cursor for destination image buffer
  unsigned char* ptrDest = dest;

  // Initialize counts buffer
  for (int i = 0; i < image::LEVELS; i++) {
    counts[i] = 0;
  }

  // Iterate through source image buffer and count grey level frequencies
  for (int i = 0; i < rows * cols; i++) {
    // Temporarily store value of current character (pixel)
    unsigned char character = src[i];

    // Increment frequency of this character in counts buffer
    counts[character]++;

    // Check if this is the current known maximum frequency
    if (counts[character] > maxCount) {
      maxCount = counts[character];
    }
  }

  // Transform counts buffer values from range [0, maxCount] to [0, 255]
  for (int i = 0; i < image::LEVELS; i++) {
    counts[i] = ((double)counts[i] / maxCount) * (image::LEVELS - 1);
  }

  // Current row and column in destination image
  int row = 0;
  int col = 0;

  // Convert character counts to histogram in destination image buffer
  for (int i = 0; i < rows * cols; i++) {
    // Use foreground colour if count for current column is equal to or higher
    // than current row value. Otherwise, use background colour.
    if (counts[col] != 0 && counts[col] >= (rows - 1 - row)) {
      *ptrDest = image::LEVEL_FOREGROUND;
    } else {
      *ptrDest = image::LEVEL_BACKGROUND;
    }

    // Increment destination image buffer cursor
    ptrDest++;

    // Increment column in destination image
    col++;

    // Increment row if reached end of current row
    if (col >= cols) {
      row++;
      col = 0;
    }
  }
}

}  // namespace image
