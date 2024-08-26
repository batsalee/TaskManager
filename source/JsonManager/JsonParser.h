/* JsonParser.h

1. 클래스 관계
JsonManager의 자식클래스

2. 용도
json 문구를 파싱해서 프로그램에 필요한 형태로 변환

3. 구현방식
rapidjson 라이브러리 활용

4. 고민
parse() 함수를 private로 선언 하는 점에 대해 고민이 있음
parse() 함수의 기능은 문자열로 주어진 json 내용을 파싱해서 Document로 리턴하는 함수이므로 어디서든 유용하게 사용될 수 있음
하지만 현재 이 프로젝트에서는 파싱과 관련된 모든 작업을 JsonParser에서 수행하도록 독립시키고 싶으므로 jsonToProgramInfo()나 jsonToTaskList()같은 함수를 호출하도록 만들었음
결과적으로 parse()는 내부에서만 사용되므로 private로 선언했음.
하지만 클래스의 재사용성을 생각한다면 다른 어디에서든 parse는 유용하게 사용 가능하므로 public으로 선언하는것이 좋을 수도 있음.
*/

#pragma once

#include "JsonManager.h"

class JsonParser : public JsonManager
{
private:
    Document parse(const std::string& file_content);

public:
    std::pair<bool, std::tuple<int, int, int>> jsonToProgramInfo(const std::string& file_content);
    QList<QList<Task>> jsonToTaskList(const std::string& file_content);
};
