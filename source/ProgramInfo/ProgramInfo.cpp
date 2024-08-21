#include "ProgramInfo.h"

#include <tuple>

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

ProgramInfo::~ProgramInfo()
{
    // program_info.json에 최근 관리일자 오늘로 변경

    Date& date = Date::instance();

    JsonSerializer json_serializer;
    std::string context = json_serializer.initializerToJson(date.getYear(), date.getMonth(), date.getDay());

    FileWriter file_writer;
    file_writer.setPath("./Data/program_info.json");
    file_writer.writeFile(context);
}

bool ProgramInfo::isTutorialNeeded()
{
    return tutorial;
}

bool ProgramInfo::isOpenedToday(Date& date)
{
    return (date.getYear() == last_managed_date_year && date.getMonth() == last_managed_date_month && date.getDay() == last_managed_date_day);
}
