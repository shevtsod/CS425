#ifndef UTIL_H
#define UTIL_H

#include <cmath>

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
 * must be castable to a floating point number.
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

  unsigned double sum = 0;

  // Get the sum of all character values
  for (int i = 0; i < SIZE; i++) {
    sum += (double)SRC[i];
  }

  // Divide sum by number of elements in buffer
  return (T)(sum / SIZE);
}

/**
 * Returns the median element given an arbitrary buffer of elements. Element
 * must be castable to a floating point number.
 * @param SRC  Buffer containing elements
 * @param SIZE Size of buffer
 * @returns    Median element in buffer
 */
template <class T>
T median(const T SRC[], const int SIZE) {
  // Handle case of empty buffer
  if (SIZE == 0) {
    return 0;
  }

  // If the size of the list is odd, return the middle element
  if (SIZE % 2 == 1) {
    return SRC[(SIZE - 1) / 2];
  }

  // If the size is even, average the two middle elements
  return (SRC[(SIZE - 1) / 2] + SRC[(SIZE - 1) / 2 - 1]) / 2;
}

/**
 * Returns the weighted sum of the given buffer of items and the given array of
 * weights of each respective item.
 */
template <class T>
T weightedSum(const T SRC[], const double WEIGHTS[], const int SIZE) {
  if (SIZE == 0) {
    return 0;
  }

  T sum = 0;

  // Iterate through the array of items and accumulate the weighted sum
  for (int i = 0; i < SIZE; i++) {
    sum += SRC[i] * WEIGHTS[i];
  }

  return sum;
}

/**
 * Returns the magnitude of a vector with the given X and Y components using the
 * forumula:
 *
 *   ||(x, y)|| = sqrt(x^2 + y^2)
 *
 * @param X x component of vector
 * @param Y y compontent of vector
 * @returns Vector magnitude
 */
template <class T>
T magnitude(const T X, const T Y) {
  return sqrt(X * X + Y * Y);
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

#endif  // UTIL_H
