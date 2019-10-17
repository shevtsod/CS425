#include "file.hpp"

#include <fstream>

namespace file {

/**
 * Reads the contents of a file at the given path and stores them in the
 * given buffer.
 *
 * @param PATH Path to input file
 * @param dest Buffer to store data into
 * @param SIZE Size of the buffer
 */
void read(const char* PATH, char* dest, const unsigned long SIZE) {
  // Open file as an input file stream
  std::ifstream file(PATH);

  // Ensure that the file exists and can be read
  if (!file.is_open()) {
    char* message;
    sprintf(message, "ERROR: Could not open file \"%s\" for reading!", PATH);
    throw message;
  }

  // Deserialize file contents into the buffer
  file.read(dest, sizeof(char) * SIZE);

  file.close();
}

/**
 * Serializes a given buffer to a file at the given path.
 *
 * @param PATH Path to output file
 * @param dest Buffer to store data into
 * @param SIZE Size of the buffer
 *
 */
void write(const char* PATH, char* dest, const unsigned long SIZE) {
  // Open file as an output file stream
  std::ofstream file(PATH);

  // Ensure that the file exists and can be read
  if (!file.is_open()) {
    char* message;
    sprintf(message, "ERROR: Could not open file \"%s\" for writing!", PATH);
    throw message;
  }

  // Serialize buffer into file
  file.write(dest, sizeof(char) * SIZE);

  file.close();
}

}  // namespace file
