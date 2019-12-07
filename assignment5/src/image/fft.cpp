#include "fft.hpp"

#include <cmath>

#include "../util/util.hpp"
#include "image.hpp"

const double PI = 3.14159265359;

namespace image {

/**
 * Computes and returns the sum of two complex numbers.
 *
 * @param a First complex number
 * @param b Second complex number
 * @returns Sum
 */
Complex complexSum(Complex a, Complex b) {
  Complex result;

  result.r = a.r + b.r;
  result.i = a.i + b.i;

  return result;
}

/**
 * Computes and returns the difference of two complex numbers.
 *
 * @param a First complex number
 * @param b Second complex number
 * @returns Sum
 */
Complex complexDiff(Complex a, Complex b) {
  Complex result;

  result.r = a.r - b.r;
  result.i = a.i - b.i;

  return result;
}

/**
 * Computes and returns the product of two complex numbers.
 *
 * @param a First complex number
 * @param b Second complex number
 * @returns Product
 */
Complex complexProduct(Complex a, Complex b) {
  Complex result;

  result.r = a.r * b.r + a.i * b.i * -1;
  result.i = a.r * b.i + a.i * b.r;

  return result;
}

/**
 * Computes and returns the product of a real and complex number.
 *
 * @param a Real number
 * @param b Complex number
 * @returns Product
 */
Complex complexProduct(double a, Complex b) {
  Complex result;

  result.r = a * b.r;
  result.i = a * b.i;

  return result;
}

/**
 * Converts a given image stored as a 2D buffer of values in range [0, 255]
 * into the given 2D buffer of the same size containing complex values with
 * real and complex components.
 *
 * @param SRC    Source 2D buffer of values in range [0, 255]
 * @param dest   Destination 2D buffer of pairs (r, i)
 * @param ROWS   Number of rows in original image
 * @param COLS   Number of columns in original image
 */
void realToComplexImage(const unsigned char* SRC,
                        Complex* dest,
                        const int ROWS,
                        const int COLS) {
  // Iterate through every pixel in the image
  for (int i = 0; i < ROWS * COLS; i++) {
    // The source image has only a real component, complex component is 0
    dest[i].r = SRC[i];
    dest[i].i = 0;
  }
}

/**
 * Converts a given image stored as a 2D buffer containing complex values with
 * real and complex components into the given 2D buffer of values in
 * range [0, 255]. Conversion is done by computing the power spectrum of
 * each complex value.
 *
 * @param SRC    Source 2D buffer of pairs (r, i)
 * @param dest   Destination 2D buffer of values in range [0, 255]
 * @param ROWS   Number of rows in original image
 * @param COLS   Number of columns in original image
 */
void complexToRealImage(const Complex* SRC,
                        unsigned char* dest,
                        const int ROWS,
                        const int COLS) {
  // Iterate through image row by row, column by column
  for (int i = 0; i < ROWS * COLS; i++) {
    // Calculate power spectrum
    double powerSpectrum = util::magnitude(SRC[i].r, SRC[i].i);

    // Scale the complex values non-linearly for visualization purposes
    double scaledPowerSpectrum = 100 * std::log(1 + powerSpectrum);

    // Clamp the value to prevent overflow before storing
    dest[i] = scaledPowerSpectrum > image::LEVEL_WHITE ? image::LEVEL_WHITE
                                                       : scaledPowerSpectrum;
  }
}

/**
 * Computes the Fast Fourier Transform of the given 1-dimensional array.
 *
 * @param SRC    Source buffer of values in range [0, 255]
 * @param dest   Destination buffer of pairs (r, i)
 * @param SIZE   Number of elements in buffer
 */
void apply1DFFT(const unsigned char* SRC, Complex* dest, const int SIZE) {
  // Buffer to store SRC with reversed indices and eventually FFT results
  Complex F1[SIZE];
  // Initial length of sub-groups
  int M = 1;
  // Number of pairs of sub-groups
  int j = SIZE / 2;
  // Number of used bits in the original buffer
  int usedBits = std::log2(SIZE);

  // Iterate through every element
  for (int i = 0; i < SIZE; i++) {
    // Compute the new index for the element (reverse bits)
    int reversedIndex = util::reverseBits(i, usedBits);

    // Store element at the reversed index in a temporary buffer
    F1[reversedIndex].r = SRC[i];
    F1[reversedIndex].i = 0;
  }

  // Successive merging
  for (int i = 0; i < usedBits; i++) {
    // Merge pairs at current level
    for (int k = 0; k < j; k++) {
      // Buffer to hold sub-group merging results
      Complex F2[2 * M];
      // Start of first sub-group
      int i1 = 2 * k * M;
      // Start of second sub-group
      int i2 = (2 * k + 1) * M;

      // Compute first half of FT using the sub-groups
      for (int u = 0; u < M; u++) {
        // F2[u] = 0.5 * (F1[i1 + u] + F1[i2 + u] * W2m^u)
        // W2m^u = e^(-j * PI * u)
        // e^(-j * PI * u) = cos(PI * u) - j * sin(PI * u)
        Complex W2mu;

        W2mu.r = std::cos(PI * u);
        W2mu.i = -std::sin(PI * u);

        F2[u] = complexProduct(
            0.5, complexSum(F1[i1 + u], complexProduct(F1[i2 + u], W2mu)));
      }

      // Compute second half of FT using the sub-groups
      for (int u = 0; u < M; u++) {
        Complex W2mu;

        W2mu.r = std::cos(PI * u);
        W2mu.i = -std::sin(PI * u);

        F2[M + u] = complexProduct(
            0.5, complexDiff(F1[i1 + u], complexProduct(F1[i2 + u], W2mu)));
      }

      // Store merge results back to results buffer
      for (int u = 0; u < 2 * M; u++) {
        F1[i1 + u] = F2[u];
      }
    }

    // Double the size of the sub-groups
    M *= 2;

    // Reduce number of sub-groups by half
    j /= 2;
  }

  // Write results to destination buffer
  for (int i = 0; i < SIZE; i++) {
    dest[i] = F1[i];
  }
}

/**
 * Computes the Fast Fourier Transform of the given 2-dimensional array.
 *
 * @param SRC    Source buffer of values in range [0, 255]
 * @param dest   Destination buffer of pairs (r, i)
 * @param ROWS   Number of rows in original image
 * @param COLS   Number of columns in original image
 */
void apply2DFFT(const unsigned char* SRC,
                Complex* dest,
                const int ROWS,
                const int COLS) {
  // Apply 1D FFT along columns
  for (int j = 0; j < COLS; j++) {
    unsigned char currentCol[ROWS];
    Complex fft[ROWS];

    // Build the column buffer
    for (int i = 0; i < ROWS; i++) {
      currentCol[i] = SRC[i * COLS + j];
    }

    apply1DFFT(currentCol, fft, ROWS);

    // Copy results to the destination column
    for (int i = 0; i < ROWS; i++) {
      dest[i * COLS + j] = fft[i];
    }
  }

  // Apply 1D FFT along rows
  for (int i = 0; i < ROWS; i++) {
    Complex fft[COLS];

    apply1DFFT(&SRC[i], fft, COLS);

    // Copy results to the destination row
    for (int j = 0; j < COLS; j++) {
      dest[i * COLS + j] = fft[j];
    }
  }
}

}  // namespace image
