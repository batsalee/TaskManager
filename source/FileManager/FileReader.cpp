#include "FileReader.h"

/* getIfstream()
현재 사용되지 않지만 rapidjson의 다른 사용방식을 위해 남겨둠
*/
std::ifstream FileReader::getIfstream()
{
    std::ifstream ifs(file_path);
    if(!ifs.is_open()) throw std::runtime_error("Failed to open file");

    return ifs;
}

/* readFile()
용도 : File 스트림을 열고 내용을 읽어옴
시퀀스 : 로컬에 저장된 일정파일을 읽어온 후 반환
특이사항 : 예외 발생시 예외는 이 함수 내부가 아닌 호출한 측에서 처리하며,
          이유는 예외가 발생한 파일의 이름을 확인하기 위함과 read 중의 예외인지 parse 중의 예외인지 구별하기 위함
*/
std::string FileReader::readFile()
{
    std::ifstream ifs(file_path);
    if(!ifs.is_open()) throw std::runtime_error("Failed to open file");

    std::stringstream buffer;
    buffer << ifs.rdbuf();
    if(ifs.fail()) throw std::runtime_error("Failed to read file");

    return buffer.str(); // RVO 유도
}
