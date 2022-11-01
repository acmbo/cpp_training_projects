#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>
#include <string>


// g++ -Wall -std=c++17  openfile_2.cc to compile
// filesystem only availabe at c++17


namespace fs = std::filesystem;

int main() {
    std::string text;

    if (fs::exists("test.txt")) {
        
        std::ifstream MyReadFile("test.txt");

        while (std::getline (MyReadFile, text)) {
            std::cout << text;
        }

        MyReadFile.close();
    }

}