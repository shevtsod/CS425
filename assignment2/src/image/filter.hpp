#ifndef IMAGE_FILTER_H
#define IMAGE_FILTER_H

namespace image {

// Mask/filter properties
const int MASK_DIMENSION = 3;
const int MASK_HALF_DIMENSION = (MASK_DIMENSION - 1) / 2;
const double MASK_NULL = -1.0;

void applyLinearFilter(const unsigned char* SRC,
                       const double MASK[MASK_DIMENSION][MASK_DIMENSION],
                       unsigned char* dest,
                       const int ROWS,
                       const int COLS);

void applyMedianFilter(const unsigned char* SRC,
                       unsigned char* dest,
                       const int ROWS,
                       const int COLS);

}  // namespace image

#endif  // IMAGE_FILTER_H
