/* FileManager.h

1. 클래스 관계
FileReader, FileWriter 클래스의 부모클래스

2. 용도
일정 파일을 로컬에 저장해야하므로 파일입출력 및 파일시스템 담당 클래스

3. 구현방식
관리하고자 하는 파일이 이미 있는지, 혹은 파일 경로에 맞는 폴더가 이미 있는지 확인하기 위해 folder_path와 file_path를 저장
만약 파일경로가 string으로 들어오면 멤버변수에 바로 넣으면 되지만
date로 들어오면 경로를 파싱해야 하므로 관련 함수 오버로딩
*/

#pragma once

#include <iostream> // 파일 open close 예외 출력용도
#include <string>
#include <filesystem>
#include <fstream>
#include "../Date/Date.h"

class FileManager
{
protected:
    std::string folder_path; // 폴더의 경로
    std::string file_path; // 파일의 경로
    // folder는 filesystem에 의해 관리받고, file은 fstream에 의해 관리받게 하기 위해 따로 기록

public:
    FileManager();

    virtual ~FileManager() {};

    // setter 오버로딩
    void setPath(Date& date); // 날짜정보로 경로를 지정하는 경우 사용
    void setPath(std::string path); // string으로 경로가 지정되는 경우 사용

    // getter
    std::string getFolderPath(); // 일정파일이 위치할 폴더의 존재유무 파악을 위해 사용
    std::string getFilePath(); // 일정파일의 존재유무 파악을 위해 사용
};
