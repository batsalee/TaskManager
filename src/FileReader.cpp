#include "FileReader.h"

std::ifstream FileReader::readFile()
{
    std::ifstream ifs(file_path);
    return ifs;
}

