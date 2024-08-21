#include "FileReader.h"

std::ifstream FileReader::getIfstream()
{
    std::ifstream ifs(file_path);
    if(!ifs) throw std::runtime_error("Failed to open file");

    return ifs;
}

/* readFile()
용도 : File 스트림을 열고 내용을 읽어옴
시퀀스 : 로컬에 저장된 일정파일을 읽어온 후 JsonManager에 의해 해당 내용(json형식)이 파싱됨
*/
std::string FileReader::readFile()
{
    std::ifstream ifs(file_path);
    if(!ifs) throw std::runtime_error("Failed to open file");

    std::stringstream buffer;
    buffer << ifs.rdbuf();
    if(ifs.fail()) throw std::runtime_error("Failed to read file");

    return buffer.str(); // RVO 유도
}
