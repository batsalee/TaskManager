/* FileWriter.h

1. 클래스 관계
FileManager.h의 자식클래스

2. 용도
로컬에 일정파일의 내용을 작성하고 저장함

3. 구현방식
FileManager 상속받고 쓰기 관련된 부분만 FileWriter에서 확장
*/

#pragma once

#include "FileManager.h"

class FileWriter : public FileManager
{
public:
    std::ofstream getOfstream(); // 현재 사용되지 않지만 rapidjson의 다른 사용방식을 위해 남겨둠
    void writeFile(const std::string& context);
};
