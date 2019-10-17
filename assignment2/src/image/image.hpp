#ifndef IMAGE_H
#define IMAGE_H

namespace image {

// Colours/grey levels
const int LEVELS = 256;
const unsigned char LEVEL_BLACK = 0;
const unsigned char LEVEL_WHITE = LEVELS - 1;

void genDownscaledImage(const unsigned char* SRC,
                        unsigned char* dest,
                        const int ROWS,
                        const int COLS,
                        const int FACTOR);

void genReducedQuantizationImage(const unsigned char* SRC,
                                 unsigned char* dest,
                                 const int ROWS,
                                 const int COLS,
                                 const int UNSET_BIT_COUNT);

}  // namespace image

#endif  // IMAGE_H
