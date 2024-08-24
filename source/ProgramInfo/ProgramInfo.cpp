#include "ProgramInfo.h"

#include <tuple>

/* ProgramInfo()
용도 : 생성자, program_info.json에서 정보 획득
시퀀스 : 프로그램 실행 시 생성되어 program_info.json 파일을 읽고 파싱해서 필요한 정보를 획득
*/
ProgramInfo::ProgramInfo()
{
    FileReader file_reader;
    JsonParser json_parser;

    file_reader.setPath("./Data/program_info.json");
    try {
        std::string file_content = file_reader.readFile(); // RVO 유도

        std::pair<bool, std::tuple<int, int, int>> program_info = json_parser.jsonToProgramInfo(file_content);
        tutorial = program_info.first;
        last_managed_date_year = std::get<0>(program_info.second);
        last_managed_date_month = std::get<1>(program_info.second);
        last_managed_date_day = std::get<2>(program_info.second);
    }
    catch(const std::runtime_error& re) {
        tutorial = true;
        last_managed_date_year = last_managed_date_month = last_managed_date_day = 0;

        std::cerr << std::string(re.what()) + "(" + file_reader.getFilePath() << ")\n";
    }
}

/* ~ProgramInfo()
용도 : 소멸자, 프로그램의 정보를 program_info.json에 저장
시퀀스 : 프로그램 실행 시의 작업이 끝나고 나면 더 이상 필요없으므로 소멸되며 현재 프로그램의 데이터를 program_info.json에 저장
*/
ProgramInfo::~ProgramInfo()
{
    Date& date = Date::instance();

    JsonSerializer json_serializer;
    std::string context = json_serializer.programInfoToJson(date.getYear(), date.getMonth(), date.getDay());

    FileWriter file_writer;
    file_writer.setPath("./Data/program_info.json");
    file_writer.writeFile(context);
}

/* isTutorialNeeded()
용도 : 프로그램 설치 후 최초 실행시 튜토리얼 필요 여부 확인
시퀀스 : 프로그램 설치 후 최초로 실행한다면 program_info.json에 tutorial 값이 true이므로 튜토리얼을 진행
*/
bool ProgramInfo::isTutorialNeeded()
{
    return tutorial;
}

/* isOpenedToday()
용도 : 오늘 프로그램을 연 적이 있다면 이미 일정 파일이 만들어져 있으니 load만 하면 되고, 오늘 처음 프로그램을 열었다면 일정 파일을 make해야 함. 이를 판단하기 위한 함수
시퀀스 : program_info.json 파일에는 가장 최근에 프로그램을 사용한 일자가 기록되어 있음.
        해당 일자를 확인한 후 오늘의 날짜와 같다면 TaskListManager 클래스의 loadTaskList() 함수를 사용, 다르다면 TaskListManager 클래스의 makeTaskList() 함수를 사용
*/
bool ProgramInfo::isOpenedToday(Date& date)
{
    return (date.getYear() == last_managed_date_year && date.getMonth() == last_managed_date_month && date.getDay() == last_managed_date_day);
}

/* getLastManagedDateYear(), getLastManagedDateMonth(), getLastManagedDateDay()
용도 : getter
시퀀스 : isOpendToday()에서 false를 리턴하면 TaskListManager 클래스의 MakeTaskList() 함수가 호출되는데 이때 아래의 getter들을 이용해 값들을 매개변수로 넘김.
        매개변수로 넘어간 값들은 오늘 이전에 가장 최근에 프로그램을 사용한 날짜이므로 해당 날짜의 일정 파일을 확인해서 남은 일정이 있다면 오늘의 일정에 append함
*/
int ProgramInfo::getLastManagedDateYear() const { return last_managed_date_year; }
int ProgramInfo::getLastManagedDateMonth() const { return last_managed_date_month; }
int ProgramInfo::getLastManagedDateDay() const { return last_managed_date_day; }
