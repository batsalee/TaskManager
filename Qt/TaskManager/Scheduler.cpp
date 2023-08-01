/* Task Schduler 자세한 구현
*
역할
1) 일정파일 생성 / 제거
2) 일정파일 내용변경(ui에서는 클릭하면 줄그어지게)
3) 프로그램 종료시 현재 일정대로 일정파일 갱신

주의사항
1) C++ 17이상 사용, 20이상 권장

*/
#include "Scheduler.h"

Scheduler::Scheduler() // 오늘 일정 관리할때
{
    getTodaysDate();
    setPath();

    createTaskfile();
    readTaskfile();
}

// 나중에 달력까지 만들게 된다면 확장을 위해
Scheduler::Scheduler(QString y, QString m, QString d) // 다른 특정 날짜 관리할때
{
    year = y; month = m; day = d;
    setPath();

    createTaskfile();
    readTaskfile();
}

Scheduler::~Scheduler() // 현재 상태 파일에 새로 쓰는 내용 갱신하기
{
    updateTaskfile();
}


/////////////////////////////////////////////////////////////////////////


// 오늘 날짜 얻기
void Scheduler::getTodaysDate()
{
    Date d;
    d.getTodaysDate();

    this->year = d.year;
    if((d.month).toInt() < 10) this->month = '0' + d.month;
    else this->month = d.month;
    if((d.day).toInt() < 10) this->day = '0' + d.day;
    else this->day = d.day;
    this->dayOfWeek = d.dayOfWeek;
}

void Scheduler::setPath()
{
    path = "./Schedule/" + year + "/" + month + "/" + day + ".txt";
}

/////////////////////////////////////////////////////////////////////////


void Scheduler::removeTask(qint32 y, qint32 x)
{
    tasks[y].removeAt(x);
    if(tasks[y].empty()) tasks.removeAt(y);
}

QList<QList<QString>> Scheduler::getTaskList()
{
    return tasks;
}

/////////////////////////////////////////////////////////////////////////


// 오늘의 일정 폴더 및 파일 생성
void Scheduler::createTaskfile()
{        
    // 폴더 없으면 만들기
    if (!std::filesystem::exists("./Schedule/" + year.toStdString() + "/" + month.toStdString()))
        std::filesystem::create_directories("./Schedule/" + year.toStdString() + "/" + month.toStdString());

    // 파일 없으면 만들기
    if (!std::filesystem::exists(path.toStdString())) {
        std::filesystem::path from("./Schedule/const_data/everyday.txt");
        std::filesystem::path to(path.toStdString());
        std::filesystem::copy(from, to);

        appendDayOfWeekTaskfile();
    }
    else { // 파일이 이미 있다면
        std::ifstream p(path.toStdString());
        char c;
        p.seekg(-1, std::ios::end);
        p.read(&c, 1);
        p.close();

        if (c != '#') { // 개별일정이 있고 && 오늘 처음 연 파일이라면
            std::ifstream in("./Schedule/const_data/everyday.txt", std::ios::binary);
            std::string s;

            // 개별일정이 있다는 뜻이므로 const.txt append해주기
            in.seekg(0, std::ios::end);
            int size = in.tellg();
            s.resize(size);
            in.seekg(0, std::ios::beg);
            in.read(&s[0], size);

            std::ofstream out(path.toStdString(), std::ios::app | std::ios::binary);
            out << '\n' << s << std::flush;

            appendDayOfWeekTaskfile();
        }
    }
}

void Scheduler::appendDayOfWeekTaskfile()
{
    std::string days[7] = {"sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "Saturday"};

    std::string days_path = "./Schedule/const_data/" + days[this->dayOfWeek.toInt()] + ".txt";
    std::ifstream in(days_path, std::ios::binary);

    std::ofstream out(path.toStdString(), std::ios::app | std::ios::binary);
    std::string s;

    // 해당 요일의 일정을 오늘의 일정 뒤에 이어붙여줌
    in.seekg(0, std::ios::end);
    int size = in.tellg();
    s.resize(size); // size-2하면 일단 다 해결되던데.. 왜이럴까
    in.seekg(0, std::ios::beg);
    in.read(&s[0], size);

    out << '\n' << s << "\n#";
    // 이미 everday.txt를 붙여왓으니 또 붙일 필요 없으므로
}

void Scheduler::readTaskfile()
{
    std::ifstream file(path.toStdString());

    std::string line; // 한 줄단위로 읽기 위해
    std::string task; // 단어 하나
    while (std::getline(file, line)) {  // task 단위로 분리해서 QList로 넣어주기
        std::stringstream ss(line);// #단위로 분리
        QList<QString> temp;
        temp.clear();
        while(std::getline(ss, task, '#')) {
            task.erase(0, task.find_first_not_of(" "));
            task.erase(task.find_last_not_of(" ") + 1); // 제일 뒤나 앞에 공백 제거용

            temp.push_back(QString::fromStdString(task));
        }
        temp.pop_front(); // 첫 # 앞의 빈공간이 들어가므로
        if(temp.size()) tasks.push_back(temp); // 마지막 #만 있는 경우도 리스트 하나가 추가되는걸 방지하기 위해
    }
}

void Scheduler::updateTaskfile()
{
    std::ofstream out(path.toStdString(), std::ios::trunc);
    for(int i = 0; i < tasks.size(); i++) {
        for(int j = 0; j < tasks[i].size(); j++) {
            out << '#' << tasks[i][j].toStdString() << ' ';
        }
        out << '\n';
    }
    out << '#';
}

//void Scheduler::removeTaskfile() {} // 일정파일/폴더 제거

