#pragma once

#include "FileManager.h"

class FileWriter : public FileManager
{
public:
    FileWriter() = default;
    FileWriter(std::string path) { file_path = path; }

    void WriteFile(std::string&);
};
