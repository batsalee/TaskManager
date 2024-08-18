/* JsonParser.h

1. 클래스 관계
JsonManager의 자식클래스
FileReader에 의해 읽혀진 내용을 Json으로 파싱 후 ScheduleFactory에서 이중리스트 생성

2. 용도
json파일을 파싱해서 이중리스트 구조로 변경

3. 구현방식
rapidjson 라이브러리 활용
*/

#pragma once

#include "JsonManager.h"

class JsonParser : public JsonManager
{
public:
    rapidjson::Document parse(std::string file_content);
    bool isOpened(std::string file_content);
    void jsonToTaskList(std::string file_content);
};
