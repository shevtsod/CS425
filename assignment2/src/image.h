namespace image {

// Colours/grey levels
const int LEVELS = 256;
const unsigned char LEVEL_FOREGROUND = 0;
const unsigned char LEVEL_BACKGROUND = 255;

unsigned char unsetBit(const unsigned char character, int position);
unsigned char average(unsigned char* characters, const unsigned long size);
void downscale(unsigned char* src,
               unsigned char* dest,
               const int rows,
               const int cols,
               const int factor);
void reduceQuantization(unsigned char* src,
                        unsigned char* dest,
                        const int rows,
                        const int cols,
                        const int unsetBitCount);
void histogram(unsigned char* src,
               unsigned char* dest,
               const int rows,
               const int cols);

}  // namespace image
