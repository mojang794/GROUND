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
        std::string key;
        T value;
        char symbol;
        while (_file >> key >> symbol >> value)
        {
            if (symbol == '=')
            {
                this->_keys[key] = value;
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