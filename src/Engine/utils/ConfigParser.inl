namespace gr
{
    template <typename T>
    ConfigFile<T>::ConfigFile() {}

    template <typename T>
    void ConfigFile<T>::open(std::string file)
    {
        std::ifstream _f(file);
        GR_ASSERT(_f.good());
        std::string key;
        T value;
        char symbol;
        while (_f >> key >> symbol >> value)
        {
            if (symbol == '=')
            {
                this->_keys[key] = value;
            }
        }
    }

    template <typename T>
    T &ConfigFile<T>::operator[](std::string key)
    {
        return _keys.at(key);
    }
}