#include "FileManager.h"

/* setPath(Date& date)
용도 : 관리중인 일정파일의 경로 지정, 입력 매개변수가 date(날짜정보)인 경우 파싱 후 지정
시퀀스 : Date객체의 년/월/일을 기반으로 파일이 저장될 폴더구조와 파일명을 지정
*/
void FileManager::setPath(Date& date)
{
    std::string year = std::to_string(date.getYear());
    std::string month = (date.getMonth() < 10) ? '0' + std::to_string(date.getMonth()) : std::to_string(date.getMonth());
    folder_path = "./Schedule/" + year + "/" + month;

    std::string file_name = (date.getDay() < 10) ? '0' + std::to_string(date.getDay()) : std::to_string(date.getDay());
    file_path = folder_path + "/" + file_name + ".json";
}

/* setPath(std::string file_name)
용도 : 관리중인 일정파일의 경로 지정, 입력 매개변수가 string인경우 해당 내용대로 지정
시퀀스 : everyday.json인 경우 경로가 고정적이므로 그대로 지정
        각 요일별.json인 경우 오늘의 요일에 맞는 파일로 지정
*/
void FileManager::setPath(std::string file_name)
{
    folder_path = "./Schedule/fixed_schedule";
    file_path = folder_path + "/" + file_name + ".json";
}

/* getFolderPath(), getFilePath()
용도 : 현재 관리중인 일정파일의 경로 획득
시퀀스 : Schedule 객체 소멸시 일정을 로컬에 저장해야 하므로 일정파일이 위치할 폴더가 존재하는지, 파일이 존재하는지 확인할때 호출
*/
std::string FileManager::getFolderPath() { return folder_path; }
std::string FileManager::getFilePath() { return file_path; }
