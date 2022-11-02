#include <iostream>
#include <fstream>

//https://cplusplus.com/reference/fstream/basic_ifstream/open/
int main() {
    std::ifstream ifs;

    std::cout << "Starting" << std::endl;

    ifs.open("test.txt", std::ifstream::in);

    char c = ifs.get();

    while(ifs.good()) {
        std::cout << c;
        c = ifs.get();
    }

    ifs.close();

    return 0;

}

