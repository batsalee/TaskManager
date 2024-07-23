#include "FileWriter.h"

void FileWriter::WriteFile(std::string& context)
{
    std::ofstream out(file_path);
    out << context;
}

