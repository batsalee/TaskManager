#include "FileManager.h"

/* FileManager()
용도 : 생성자, 초기값 설정
시퀀스 : 객체 생성시 Date를 참조해서 오늘 날짜 정보를 기반으로 경로 설정

- 초기값 설정의 이유
대부분의 경우 현재 관리중인 날짜의 파일을 읽고 쓰기때문에, 객체 생성 직후 대부분의 경우 setPath(Date&)를 호출하므로 코드 중복을 줄이고 편의성을 높이기 위해 생성자에서 호출
또한 Date 객체의 생성자에 내 실수를 방지할 수 있는 장치를 만들어뒀기에 실수 방지의 연장선
*/
FileManager::FileManager()
{
    setPath(Date::instance()); // 현재 관리중인 날짜로 경로 설정
}

/* setPath(Date& date)
용도 : 관리중인 날짜를 기반으로 일정파일의 경로 지정
시퀀스 : 날짜 지정 시 입력 매개변수가 Date객체(날짜정보)인 경우 Date객체의 년/월/일을 참조하고 파싱해서 파일이 저장될 폴더구조와 파일명을 지정
*/
void FileManager::setPath(Date& date)
{
    std::string year = std::to_string(date.getYear());
    std::string month = (date.getMonth() < 10) ? '0' + std::to_string(date.getMonth()) : std::to_string(date.getMonth());
    folder_path = "./Data/" + year + "/" + month;

    std::string file_name = (date.getDay() < 10) ? '0' + std::to_string(date.getDay()) : std::to_string(date.getDay());
    file_path = folder_path + "/" + file_name + ".json";
}

/* setPath(std::string file_name)
용도 : 관리중인 파일명을 기반으로 일정파일의 경로 지정
      ProgramInfo 파일을 읽거나, fixed_schedule인 매일할일, 해당 요일에 할일 등을 저장해둔 파일의 경로를 지정할 때 사용
시퀀스 : 날짜 지정 시 입력 매개변수가 string(파일명)인 경우 파일 명을 기반으로 경로 지정

- 이 경우 배포시에 이미 폴더 구조가 지정되어 있으므로 folder_path는 필요하지 않음
*/
void FileManager::setPath(std::string file_name)
{
    file_path = file_name;
}

/* getFolderPath(), getFilePath()
용도 : 현재 관리중인 일정파일의 경로 획득
시퀀스 : 오늘 날짜로 사전에 등록한 일정이 있는지 확인하기 위해 getFilePath() 호출
        날짜 변경 혹은 프로그램 종료 시 일정을 로컬에 저장해야 하므로 일정파일이 위치할 폴더가 존재하는지 확인하기 위해 getFolderPath() 호출
*/
std::string FileManager::getFolderPath() const { return folder_path; }
std::string FileManager::getFilePath() const { return file_path; }

