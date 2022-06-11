#pragma once

#include <map>
#include <fstream>
#include <iostream>
#include "../GR_cross_definitions.h"

namespace gr
{
    template<typename T>
    class ConfigFile
    {
    public:
        ConfigFile();

        void open(std::string file);

        T& operator[](std::string key);
    private:
        std::map<std::string, T> _keys;
    };
}

#include "ConfigParser.inl"