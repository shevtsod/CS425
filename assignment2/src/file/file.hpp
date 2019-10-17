#ifndef FILE_H
#define FILE_H

namespace file {

void read(const char* PATH, char* dest, const unsigned long SIZE);

void write(const char* PATH, char* dest, const unsigned long SIZE);

}  // namespace file

#endif  // FILE_H
