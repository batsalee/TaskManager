/* FileReader.h

1. 클래스 관계
FileManager.h의 자식클래스

2. 용도
로컬에 저장된 File의 내용을 읽어옴

3. 구현방식
FileManager 상속받고 읽기 관련된 부분만 FileReader에서 확장
*/

#pragma once

#include "FileManager.h"

class FileReader : public FileManager
{
public:
    std::ifstream getIfstream(); // 현재 사용되지 않지만 rapidjson의 다른 사용방식을 위해 남겨둠
    std::string readFile();
};
