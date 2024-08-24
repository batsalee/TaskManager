/* JsonSerializer.h

1. 클래스 관계
JsonManager의 자식클래스

2. 용도
프로그램 내부의 데이터를 json 형태로 변경

3. 구현방식
rapidjson 라이브러리 활용
*/

#pragma once

#include "JsonManager.h"

class JsonSerializer : public JsonManager
{
public:
    std::string programInfoToJson(int y, int m, int d);
    std::string taskListToJson(const QList<QList<Task>>& task_list);
};
