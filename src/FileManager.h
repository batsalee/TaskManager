#pragma once

#include <string>

class FileManager
{
protected:
    std::string file_path;

public:
    virtual ~FileManager() {};
};
