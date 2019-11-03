#ifndef IMAGE_FILTER_H
#define IMAGE_FILTER_H

namespace image {

// Mask/filter properties
const int MASK_SIZE = 3;
const int MASK_SIZE_HALF = (MASK_SIZE - 1) / 2;
const double MASK_NULL = -1.0;

void applyLinearFilter(const unsigned char* SRC,
                       const double MASK[MASK_SIZE][MASK_SIZE],
                       unsigned char* dest,
                       const int ROWS,
                       const int COLS);

void applyMedianFilter(const unsigned char* SRC,
                       unsigned char* dest,
                       const int ROWS,
                       const int COLS);

void genGradient(const unsigned char* SRC,
                 unsigned char* dest,
                 const int ROWS,
                 const int COLS);

void applyLaplaceSharpening(const unsigned char* SRC,
                            unsigned char* dest,
                            const int ROWS,
                            const int COLS,
                            const double WEIGHT);

}  // namespace image

#endif  // IMAGE_FILTER_H
