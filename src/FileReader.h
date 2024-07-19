#pragma once

#include <fstream>

#include "FileManager.h"

class FileReader : public FileManager
{
public:
    FileReader() = default;
    FileReader(std::string path) { file_path = path; }

    std::string readFile();
};
