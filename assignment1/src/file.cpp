#include <fstream>

#include "file.h"

namespace file {

/**
 * Reads the contents of a file at the given path and stores them in the
 * given buffer.
 *
 * @param path Path to input file
 * @param buffer Buffer to store data into
 * @param length Length of the buffer
 */
void read(const char* path, char* buffer, size_t length) {
  // Open file as an input file stream
  std::ifstream file(path);

  // Ensure that the file exists and can be read
  if (!file.is_open()) {
    char* message;
    sprintf(message, "ERROR: Could not open file \"%s\" for reading!", path);
    throw message;
  }

  // Deserialize file contents into the buffer
  file.read(buffer, sizeof(char) * length);

  file.close();
}

/**
 * Serializes a given buffer to a file at the given path.
 *
 * @param path Path to output file
 * @param buffer Buffer to store data into
 * @param length Length of the buffer
 *
 */
void write(const char* path, char* buffer, size_t length) {
  // Open file as an output file stream
  std::ofstream file(path);

  // Ensure that the file exists and can be read
  if (!file.is_open()) {
    char* message;
    sprintf(message, "ERROR: Could not open file \"%s\" for writing!", path);
    throw message;
  }

  // Serialize buffer into file
  file.write(buffer, sizeof(char) * length);

  file.close();
}

}  // namespace file
