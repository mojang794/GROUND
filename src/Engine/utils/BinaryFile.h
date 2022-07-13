#pragma once

#include <string>

namespace gr
{
    class BinaryFile
    {
    public:
        static void ConvertFileToBinary(std::string baseFile, std::string binaryFile);
        static void ConvertBinaryToFile(std::string binaryFile, std::string newFile);
    };
}