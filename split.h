#ifndef SPLIT
#define SPLIT

#include <string>

void SplitBySize(std::string file_name, int size_of_piece_bytes);

void SplitByCount(std::string file_name, int number_of_parts);

#endif