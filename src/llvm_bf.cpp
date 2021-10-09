#include <iostream>
#include <string>
#include <cstdint>
#include <array>
std::array<std::uint8_t, 1000000> data;
#include <fstream>

int main(int argc,char* argv[]){
    std::ifstream inputstream(argv[1]);
    std::cout << "Hello" << std::endl;
    
    return 0;
}