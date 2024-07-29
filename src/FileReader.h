#pragma once

#include "FileManager.h"

class FileReader : public FileManager
{
public:
    FileReader() = default;
    FileReader(std::string path) { file_path = path; }

    std::string readFile();
};
