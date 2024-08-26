/* FileManager.h

1. 클래스 관계
FileReader, FileWriter 클래스의 부모클래스
Date 클래스를 참조해서 경로 설정 시 사용

2. 용도
일정 파일을 로컬에 저장하고 읽어와야하므로 파일입출력 및 파일시스템 담당 클래스

3. 구현방식
- 클래스간 역할 분담 및 확장
부모클래스인 FileManager 클래스는 파일의 경로 관련 기능만 구현
자식클래스인 FileReader 클래스는 파일의 내용을 읽어오는 기능을 확장
자식클래스인 FileWriter 클래스는 파일에 내용을 쓰는 기능을 확장

- 폴더경로와 파일경로를 따로 저장
파일 및 폴더의 존재 유무 파악을 위해 filesystem 라이브러리 활용 및 이를 위해 폴더경로와 파일경로를 따로 저장
FileWriter 클래스에서 저장하는 시점에 파일 경로에 맞는 폴더의 존재 유무 파악을 위해 folder_path를 활용
일정 파일이 이미 존재하는지 여부 파악을 위해 file_path를 활용

- 함수 오버로딩
날짜를 기반으로 파일 경로를 설정하기 위해 date를 받는 setPath(Date&)와,
고정 파일의 경우 파일명을 기반으로 파일 경로를 설정하기 위해 std::string을 받는 setPath(std::string&)을 구현
*/

#pragma once

#include <iostream> // 파일여닫을때 cerr 출력용도
#include <string>
#include <filesystem>
#include <fstream>

#include "../Date/Date.h"

class FileManager
{
protected:
    std::string folder_path; // 폴더의 경로
    std::string file_path; // 파일의 경로

public:
    FileManager(); // 객체 생성 시 현재 관리중인 날짜를 기반으로 경로 설정
    virtual ~FileManager() {};

    // getter
    std::string getFolderPath() const; // 일정파일이 위치할 폴더의 존재유무 파악을 위해 사용
    std::string getFilePath() const; // 일정파일의 존재유무 파악을 위해 사용

    // setter 오버로딩
    void setPath(Date& date); // 날짜정보로 경로를 지정하는 경우 사용
    void setPath(std::string path); // string으로 경로가 지정되는 경우 사용
};
