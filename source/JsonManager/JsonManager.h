/* JsonManager.h

1. 클래스 관계
JsonParser와 JsonSerializer의 부모클래스
FileManager클래스에 의해 읽혀진 context를 json으로 파싱
Schedule 클래스 소멸시 이중리스트를 json으로 파싱 후 FileManager에 의해 저장

2. 용도
일정 정보를 로컬에 json으로 저장하고, 저장된 json을 읽어와서 파싱하는 용도

3. 구현방식
rapidjson 라이브러리를 사용해서 파싱 및 시리얼라이징
*/

#pragma once

#include <iostream> // 파일여닫을때 cerr 출력용도

#include "../Task/Task.h"

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/error/en.h"
using namespace rapidjson;

class JsonManager
{
public:
    virtual ~JsonManager() {};
};
