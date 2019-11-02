#include "image.hpp"

#include "../util/util.hpp"

namespace image {

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
 * @param SRC    Buffer containing original image
 * @param dest   Destination buffer for downscaled image
 * @param ROWS   Number of rows in original image
 * @param COLS   Number of columns in original image
 * @param FACTOR Downscaling factor
 */
void genDownscaledImage(unsigned char* SRC,
                        unsigned char* dest,
                        const int ROWS,
                        const int COLS,
                        const int FACTOR) {
  // Ensure that the scaling factor is a power of 2
  if (FACTOR <= 0 || (FACTOR & (FACTOR - 1) == 0)) {
    throw "ERROR: Scaling factor must be a power of 2!";
  }

  // Dimensions of destination image
  const int DEST_ROWS = ROWS / FACTOR;
  const int DEST_COLS = COLS / FACTOR;
  // Current column in source image
  int col = 0;
  // Cursor for source buffer
  unsigned char* ptrSrc = SRC;

  // Divide the source image into blocks based on the destination image size
  for (int i = 0; i < DEST_ROWS * DEST_COLS; i++) {
    // Smaller buffer to hold the block's pixels
    unsigned char block[FACTOR][FACTOR];

    // Populate this block with the corresponding pixels from the source image
    for (int j = 0; j < FACTOR; j++) {
      for (int k = 0; k < FACTOR; k++) {
        // Index element in source buffer using row major order
        block[j][k] = ptrSrc[COLS * j + k];
      }
    }

    // Average the values of the pixels at this block into the
    // destination buffer
    dest[i] = util::average(&block[0][0], FACTOR * FACTOR);

    // Increment current column in source image
    col += FACTOR;

    // Check if reached end of current row
    if (col < COLS) {
      // If not end of row, shift left one block
      ptrSrc += FACTOR;
    } else {
      // If end of row, shift down one block
      ptrSrc += FACTOR + COLS * (FACTOR - 1);

      col = 0;
    }
  }
}

/**
 * Produces an image with a lower bit quantization into the destination buffer.
 * The quantization is reduced by unsetting the N lowest order bits per pixel.
 *
 * @param SRC             Buffer containing original image
 * @param dest            Destination buffer for reduced quantization image
 * @param ROWS            Number of rows in original image
 * @param COLS            Number of columns in original image
 * @param UNSET_BIT_COUNT Number of lowest order bits to unset
 */
void genReducedQuantizationImage(const unsigned char* SRC,
                                 unsigned char* dest,
                                 const int ROWS,
                                 const int COLS,
                                 const int UNSET_BIT_COUNT) {
  // Ensure that no more bits are unset than are available in a character
  if (UNSET_BIT_COUNT >= sizeof(char) * 8) {
    throw "ERROR: Bit position out of range!";
  }

  // Loop through the entire source image pixel by pixel
  for (int i = 0; i < ROWS * COLS; i++) {
    // Temporarily store value of current character (pixel)
    unsigned char character = SRC[i];

    // Unset the lowest order N bits from the source image buffer and store in
    // destination image buffer at the same location
    for (int j = 0; j < UNSET_BIT_COUNT; j++) {
      character = util::unsetBit<unsigned char>(character, j);
    }

    // Set character with unset bits
    dest[i] = character;
  }
}

}  // namespace image
