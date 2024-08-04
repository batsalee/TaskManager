#include "FileReader.h"

/* readFile()
용도 : File 스트림을 열고 내용을 읽어옴
시퀀스 : 로컬에 저장된 일정파일을 읽어온 후 JsonManager에 의해 해당 내용(json형식)이 파싱됨
고민 : rapidjson 라이브러리에 string으로부터 파싱이 아닌, stream으로부터의 파싱기능이 있음
      해당 기능을 사용하는쪽이 오버헤드를 한번 줄이는것이므로 변경해볼 예정인데
      문제는 그럼 readFile함수는 그저 ifstream을 return하는 기능만 남게 됨.
      존재 의의에 대한 고민중
*/
std::string FileReader::readFile()
{
    std::ifstream ifs(file_path);
    std::string file_content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    return file_content;
}

