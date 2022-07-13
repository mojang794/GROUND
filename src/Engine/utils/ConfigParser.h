#pragma once

#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include "../GR_cross_definitions.h"

namespace gr
{
    template<typename T>
    class ConfigFile
    {
    public:
        ConfigFile();

        void copy(ConfigFile& e);
        void open(std::string file);
        /**
         * @brief Change the values in the config file. 
         * Basically when we change the map values, this function write the data in the file.
         */
        void ChangeValues();

        int GetSize() const;
        T& operator[](std::string key);

        std::map<std::string, T> _keys;
    private:
        std::string filename;
    };
}

#include "ConfigParser.inl"