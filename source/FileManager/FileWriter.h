/* FileWriter.h

1. 클래스 관계
FileManager.h의 자식클래스

2. 용도
로컬에 일정파일의 내용을 작성하고 저장함
Schedule객체가 소멸할때 이중리스트의 내용을 JsonSerializer가 json으로 변경하고
FileWriter가 해당 json 내용을 로컬에 File로 저장

3. 구현방식
FileManager 상속받고 쓰기 관련된 부분만 FileWriter에 구현
*/

#pragma once

#include "FileManager.h"

class FileWriter : public FileManager
{
public:
    void writeFile(std::string&);
};
