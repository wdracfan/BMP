#include <string>
#include <fstream>
#include <filesystem>
// #include <iostream>

void SplitBySize(std::string file_name, int size_of_piece_bytes) {
    std::ifstream file(file_name, std::ios::in | std::ios::binary);
    int size = std::filesystem::file_size(file_name);
    int cnt = 1;
    char* buffer = new char[size_of_piece_bytes]; 
    while (size > (cnt - 1) * size_of_piece_bytes) {
        int bytes_to_read = std::min(size_of_piece_bytes, size - (cnt - 1) * size_of_piece_bytes);
        file.read(buffer, bytes_to_read);
        std::ofstream part(file_name + ".part" + std::to_string(cnt), std::ios::out | std::ios::binary);
        part.write(buffer, bytes_to_read);
        ++cnt;
    }
    delete buffer;
}

void SplitByCount(std::string file_name, int number_of_parts) {
    int size = std::filesystem::file_size(file_name);
    SplitBySize(file_name, (size + number_of_parts - 1) / number_of_parts);
}