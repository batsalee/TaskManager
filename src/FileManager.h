#pragma once

#include <string>
#include <fstream>

class FileManager
{
protected:
    std::string file_path;

public:
    virtual ~FileManager() {};
};
