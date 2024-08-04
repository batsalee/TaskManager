/* FileManager.h

1. 클래스 관계
FileReader, FileWriter 클래스의 부모클래스

2. 용도
일정 파일을 로컬에 저장해야하므로 파일입출력 및 파일시스템 담당 클래스

3. 구현방식
FileReader 클래스는 ScheduleFactory 클래스와 커플링이 생길 수 밖에 없음
그러므로 의존성을 약화시키기 위해 상속관계로 구현 후 virtual 함수를 호출하도록 만들어서 호출하게 만듬

FileWriter클래스 또한 Schedule 객체가 소멸하는 시점에 Schedule 객체에 의해 호출되거나
Visitor 패턴을 구현해서 호출되어야 하므로 마찬가지로 virtual로 구현 후 호출
*/

#pragma once

#include <string>
#include <fstream>

class FileManager
{
protected:
    std::string file_path; // 파일의 경로

public:
    virtual ~FileManager() {};
};
