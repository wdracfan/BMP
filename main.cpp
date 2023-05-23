#include <fstream>
#include <iostream>
#include <string>

#include "split.h"

#pragma pack(2)
struct Header {
    uint16_t type; // 2
    uint32_t size; // 4
    uint16_t reserved1; // 2
    uint16_t reserved2; // 2
    uint32_t offbits; // 4

    void Print() {
        std::cout << "header:\n";
        std::cout << "type: " << type << "; size: " << size << "; reserved1: " << reserved1;
        std::cout << "; reserved2: " << reserved2 << "; offbits: " << offbits << "\n";
    }
};
#pragma pack(0)

// поддерживает bitmapinfo размеров 40, 108, 124 (32-битные поля)
// нужно ли делать отдельную структуру для версии CORE (16-битные поля)?
#pragma pack(2)
struct Info {
    uint32_t size; // 4, version
    uint32_t width; // 4
    uint32_t height; // 4
    uint16_t planes; // 2
    uint16_t bit_count; // 2
    uint32_t compression; // 4
    uint32_t size_image; // 4
    uint32_t x_pels_per_meter; // 4
    uint32_t y_pels_per_meter; // 4
    uint32_t clr_used; // 4
    uint32_t clr_important; // 4
    uint32_t red_mask; // 4
    uint32_t green_mask; // 4
    uint32_t blue_mask; // 4
    uint32_t alpha_mask; // 4
    uint32_t cs_type; // 4
    uint32_t endpoints[9]; // 36, адекватно пока не выводится; если нужно, пофикшу
    uint32_t gamma_red; // 4
    uint32_t gamma_green; // 4
    uint32_t gamma_blue; // 4
    uint32_t intent; // 4
    uint32_t profile_data; // 4
    uint32_t profile_size; // 4
    uint32_t reserved; // 4


    void Print(int info_size) {
        std::cout << "info:\n";
        std::cout << "size: " << size << "; width: " << width << "; height: " << height << "; planes: " << planes;
        std::cout << "; bit_count: " << bit_count << "; compression: " << compression << "; size_image: " << size_image;
        std::cout << "; x_pels_per_meter: " << x_pels_per_meter << "; y_pels_per_meter: " << y_pels_per_meter;
        if (info_size > 40) {
            std::cout << "; clr_used: " << clr_used << "; clr_important: " << clr_important;
            std::cout << "; red_mask: " << red_mask << "; green_mask: " << green_mask << "; blue_mask: " << blue_mask;
            std::cout << "; alpha_mask: " << alpha_mask << "; cs_type: " << cs_type << "; endpoints: " << endpoints;
            std::cout << "; gamma_red: " << gamma_red << "; gamma_green: " << gamma_green << "; gamma_blue: " << gamma_blue;
            if (info_size > 108) {
                std::cout << "; intent: " << intent << "; profile_data: " << profile_data << "; profile_size: " << profile_size;
                std::cout << "; reserved: " << reserved << "\n";
            } else {
                std::cout << "\n";
            }
        } else {
            std::cout << "\n";
        }
    }
};
#pragma pack(0)

int main() {
    std::string file_name;
    getline(std::cin, file_name);
    std::ifstream file(file_name, std::ios::in | std::ios::binary);

    // чтение hdr
    Header hdr;
    file.read((char *)(&hdr), sizeof(hdr));
    hdr.Print();
    
    // чтение version info
    Info info;
    file.read((char *)(&info), hdr.offbits - 14);
    info.Print(hdr.offbits - 14);

    // тестирование утилиты split
    SplitByCount("test/testfile.txt", 5);
    SplitBySize("test/test2.bmp", 200000);
}