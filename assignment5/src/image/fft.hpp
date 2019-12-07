#ifndef IMAGE_FFT_H
#define IMAGE_FFT_H

namespace image {

/**
 * Represents a complex number with real and complex components as a pair
 * of values (r, i).
 */
struct Complex {
  double r;
  double i;
};

Complex complexSum(Complex a, Complex b);

Complex complexDiff(Complex a, Complex b);

Complex complexProduct(Complex a, Complex b);

Complex complexProduct(double a, Complex b);

void realToComplexImage(const unsigned char* SRC,
                        Complex* dest,
                        const int ROWS,
                        const int COLS);

void complexToRealImage(const Complex* SRC,
                        unsigned char* dest,
                        const int ROWS,
                        const int COLS);

void apply1DFFT(const unsigned char* SRC, Complex* dest, const int SIZE);

void apply2DFFT(const unsigned char* SRC,
                Complex* dest,
                const int ROWS,
                const int COLS);

}  // namespace image

#endif  // IMAGE_FFT_H
