#ifndef H_UTIL
#define H_UTIL

namespace util {

/**
 * Returns a new element with the bit at the given position unset.
 * Least significant bit = position 0.
 *
 * @param SRC Original element
 * @param POS Bit position to unset
 * @returns   Element with bit at given position unset
 */
template <class T>
T unsetBit(const T SRC, const int POS) {
  return SRC & ~(1 << POS);
}

/**
 * Returns the average element given an arbitrary buffer of elements. Element
 * must be castable to integer.
 *
 * @param SRC  Buffer containing elements to average
 * @param SIZE Size of buffer
 * @returns    Average element in buffer
 */
template <class T>
T average(const T SRC[], const int SIZE) {
  // Handle case of empty buffer
  if (SIZE == 0) {
    return 0;
  }

  unsigned long sum = 0;

  // Get the sum of all character values
  for (int i = 0; i < SIZE; i++) {
    sum += (int)SRC[i];
  }

  // Divide sum by number of elements in buffer
  return (T)((double)sum / SIZE);
}

/**
 * Sorts a given buffer into a destination buffer of the same size. Sorting is
 * implemented using the insertion sort algorithm.
 *
 * @param SRC  Original buffer
 * @param dest Destination buffer with sorted elements
 */
template <class T>
void insertionSort(const T SRC[], T dest[], const int SIZE) {
  // Copy source buffer to destination buffer
  for (int i = 0; i < SIZE; i++) {
    dest[i] = SRC[i];
  }

  // Apply insertion sort to destination buffer
  for (int i = 1; i < SIZE; i++) {
    for (int j = i; j > 0 && dest[j - 1] > dest[j]; j--) {
      // Swap elements at index j and j - 1
      T temp = dest[j];
      dest[j] = dest[j - 1];
      dest[j - 1] = temp;
    }
  }
}

}  // namespace util

#endif  // H_UTIL
