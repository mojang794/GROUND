#include "BinaryFile.h"
#include "../GR_cross_definitions.h"
#include <iostream>
#include <fstream>

namespace gr
{
    void BinaryFile::ConvertFileToBinary(std::string baseFile, std::string binaryFile)
    {
        std::ifstream base(baseFile, std::ios::in | std::ios::binary);
        std::ofstream binary(binaryFile, std::ios::out | std::ios::app);

        char ch;
        while(!base.eof()) {
            ch = base.get();
            binary.put(ch);
        }   

        base.close();
        binary.close();
    }
    
    void BinaryFile::ConvertBinaryToFile(std::string binaryFile, std::string newFile)
    {
        std::ifstream base(binaryFile, std::ios::in | std::ios::binary);
        std::ofstream binary(newFile, std::ios::out | std::ios::app);

        char ch;
        while(!base.eof()) {
            ch = base.get();
            binary.put(ch);
        }   

        base.close();
        binary.close();
    }
}