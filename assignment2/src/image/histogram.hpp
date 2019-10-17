#ifndef IMAGE_HISTOGRAM_H
#define IMAGE_HISTOGRAM_H

namespace image {

void genHistogram(const unsigned char* SRC,
                  int dest[],
                  const int ROWS,
                  const int COLS);

void genCumulativeHistogram(const int SRC[], int dest[]);

void genNormalizedHistogram(const int SRC[], int dest[], const double FACTOR);

void genHistogramImage(const int SRC[], unsigned char* dest);

void genEqualizedHistogramImage(const unsigned char* SRC,
                                unsigned char* dest,
                                const int ROWS,
                                const int COLS);

}  // namespace image

#endif  // IMAGE_HISTOGRAM_H
