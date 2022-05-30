#include "ConfigParser.h"
#include <iostream>
#include <fstream>
#include "../GR_cross_definitions.h"

namespace gr
{
    template<typename T>
    ConfigFile<T>::ConfigFile()
    {
        
    }
    
    template<typename T>
    void ConfigFile<T>::open(std::string file)
    {
        std::ifstream _f(file);
        GR_ASSERT(_f.good());
        std::string key;
        T value;
        char symbol;
        while(_f >> key >> symbol >> value)
        {
            if (symbol == '=') {
                continue;
            }
            else {
                gr::LogWarning("Cannot read a line, maybe you didn't put = symbol");
                break;
            }

            if (key.at(0) == '[' || key.at(0) == ';') {
                continue;
            }
            else {
                this->_keys[key] = value;
            }
        }
    }
    
    template<typename T>
    T& ConfigFile<T>::operator [](std::string key)
    {
        return _keys.at(key);
    }
}