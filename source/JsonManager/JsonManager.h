/* JsonManager.h

1. 클래스 관계
JsonParser와 JsonSerializer의 부모클래스

2. 용도
json 문구를 파싱하고, 데이터를 json으로 시리얼라이징하는 용도

3. 구현방식
rapidjson 라이브러리를 사용
자식클래스인 JsonParser 클래스는 json형식의 문자열을 파싱하고, 원하는 형태로 변환하는 기능을 구현
자식클래스인 JsonSerializer 클래스는 프로그램 내부 데이터를 json형태로 파싱하는 기능을 구현
*/

#pragma once



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
