/* ProgramInfo.h

1. 클래스 관계
FileReader 클래스와 JsonParser를 호출해서 활용하는 클래스

2. 용도
프로그램 실행 시 프로그램 관련 정보가 저장된 program_info.json 파일을 해석해서 프로그램 정보를 획득함

3. 구현방식
FileReader를 통해 program_info.json 파일을 읽어오고, JsonParser를 통해 파싱한 결과에서 필요한 정보를 추출함
해당 정보를 이용해서 프로그램 실행시의 동작이 결정됨
작업이 끝나고 나면 내용을 갱신해서 JsonSerializer와 FileWriter를 활용해 다시 program_info.json 파일에 프로그램 정보를 저장함
*/

#pragma once

#include "../FileManager/FileReader.h"
#include "../FileManager/FileWriter.h"
#include "../JsonManager/JsonParser.h"
#include "../JsonManager/JsonSerializer.h"
#include "../Tutorial/Tutorial.h"

class ProgramInfo
{
private:
    bool tutorial;
    int last_managed_date_year;
    int last_managed_date_month;
    int last_managed_date_day;

public:
    // 생성자, 소멸자
    ProgramInfo();
    ~ProgramInfo();

    // 정보 확인용 bool함수
    bool isTutorialNeeded();
    bool isOpenedToday(Date& date);

    // getter
    int getLastManagedDateYear() const;
    int getLastManagedDateMonth() const;
    int getLastManagedDateDay() const;
};
