namespace gr
{
    template <typename T>
    ConfigFile<T>::ConfigFile() {}
    
    template<typename T>
    void ConfigFile<T>::copy(ConfigFile& e)
    {
        _keys = e._keys;
    }

    template <typename T>
    void ConfigFile<T>::open(std::string file)
    {
        this->filename = file;
        std::ifstream _file;
        _file.open(file);
        GR_ASSERT(_file.good());
        if (_file.is_open()) 
        {
            std::string line;
            while(std::getline(_file, line)) 
            {
                line.erase(std::remove_if(line.begin(), line.end(), isspace),line.end());
                if (line[0] == '#' || line.empty()) continue;

                auto delimiterPos = line.find("=");
                auto name = line.substr(0, delimiterPos);
                auto value = line.substr(delimiterPos + 1);

                if (typeid(T) == typeid(int)) {
                    _keys[name] = std::stoi(value);
                } else if (typeid(T) == typeid(double)) {
                    _keys[name] = std::stod(value);
                } else if (typeid(T) == typeid(float)) {
                    _keys[name] = std::stof(value);
                } else if (typeid(T) == typeid(bool)) {
                    _keys[name] = std::stoi(value);
                }
            }
        }
        _file.close();
    }
    
    template<typename T>
    void ConfigFile<T>::ChangeValues()
    {
        std::ofstream _file(filename, std::ios::in);
        if (!_file.is_open()) {
            gr::LogError("Cannot change values of a file that is not opened.");
        }
        else {
            gr::Print(GR_TO_CSTRING("[FILE]", filename), "Saving data in file...");
            for (auto& e : _keys) {
                _file << e.first << " = " << e.second << std::endl;
            }
        }
        _file.close();
    }
    
    template<typename T>
    int ConfigFile<T>::GetSize() const
    {
        return this->_keys.size();
    }

    template <typename T>
    T &ConfigFile<T>::operator[](std::string key)
    {
        return _keys.at(key);
    }
}