/* JsonParser.h

1. 클래스 관계
JsonManager의 자식클래스

2. 용도
json 문구를 파싱해서 프로그램에 필요한 형태로 변환

3. 구현방식
rapidjson 라이브러리 활용
*/

#pragma once

#include "JsonManager.h"

class JsonParser : public JsonManager
{
public:
    Document parse(const std::string& file_content);
    std::pair<bool, std::tuple<int, int, int>> jsonToProgramInfo(const std::string& file_content);
    QList<QList<Task>> jsonToTaskList(const std::string& file_content);
};
