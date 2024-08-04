/* FileReader.h

1. 클래스 관계
FileManager.h의 자식클래스

2. 용도
로컬에 저장된 File을 읽어옴
읽어온 결과는 JsonParser에 의해 이중리스트로 파싱됨

3. 구현방식
FileManager.h의 virtual readFrile()의 구현부
*/

#pragma once

#include "FileManager.h"

class FileReader : public FileManager
{
public:
    std::string readFile();
};
