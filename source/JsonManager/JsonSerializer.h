/* JsonSerializer.h

1. 클래스 관계
JsonManager의 자식클래스
Schedule 객체 소멸시 이중리스트를 json으로 serializing한 후 해당 내용을 FileWriter가 로컬에 저장

2. 용도
이중리스트를 json으로 변경

3. 구현방식
rapidjson 라이브러리 활용
*/

#pragma once

#include "JsonManager.h"
#include "../Schedule/Schedule.h"

class JsonSerializer : public JsonManager
{
public:
    std::string taskListToJson(QList<QList<Task>>& task_list);
};
