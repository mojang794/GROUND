#pragma once

#include <map>

namespace gr
{
    template<typename T>
    class ConfigFile
    {
    public:
        ConfigFile();

        void open(std::string file);

        T& operator [](std::string key);
    private:
        std::map<std::string, T> _keys;
    };
}