#include "FileWriter.h"

void FileWriter::writeFile(std::string& context)
{
    std::ofstream out(file_path);
    out << context;
}

