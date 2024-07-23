#include "FileReader.h"

std::string FileReader::ReadFile()
{
    std::ifstream ifs(file_path);
    std::string file_content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    return file_content;
}

