#include "Date.h"

/* Date()
용도 : 생성자, 초기값 설정
시퀀스 : 객체 생성시 오늘 날짜 정보를 획득해서 멤버 변수 값 설정

- 초기값 설정의 이유
처음 Date::instance()로 객체 생성시 값을 설정하지 않으면 int 멤버변수들에 쓰레기값이 들어있으므로 예상하못지 한 결과나가 올 수 있음
물론 프로그램 시작과 동시에 Date객체 생성 후 setToCurrentDate()함수를 호출하도록 구현하면 되지만 혹시 모를 내 실수를 미연에 방지하기 위해 그냥 초기값으로 설정해버리기로 함
*/
Date::Date()
{
    setToCurrentDate();
}

/* instance()
용도 : Date 싱글턴 객체 획득
시퀀스 : FileManager가 관리중인 날짜를 기반으로 파일의 경로를 설정하므로 날짜 정보 획득 시 사용
*/
Date& Date::instance()
{
    static Date instance;
    return instance;
}

/* setDate()
용도 : 관리할 날짜 변경 시 관련 내용 처리
시퀀스 : 사용자의 날짜 변경 -> dateChanged() 시그널 발생 -> TaskListManager의 saveTaskList() slot 호출 -> 기존의 일정파일이 저장됨
        -> 다시 setDate()로 돌아와서 날짜 정보 갱신 -> readyToLoad() 시그널 발생 -> TaskListManager의 loadTaskList() slot 호출 -> 변경된 날짜의 일정파일을 load함
*/
void Date::setDate(QDate& q_date)
{
    emit dateChanged(); // 사용자가 날짜를 변경하면 발생 -> 일정파일을 저장하도록 saveTaskList() 호출

    year = q_date.year();
    month = q_date.month();
    day = q_date.day();
    day_of_week = q_date.dayOfWeek();

    emit readyToLoad(); // 날짜 갱신됐으니 이 날짜로 다시 불러오라고 시그널 발생시킴 -> loadTaskList() 호출
}

/* setToCurrentDate()
용도 : 오늘의 날짜(년, 월, 일, 요일) 획득 및 멤버 변수 값 설정
시퀀스 : 프로그램 최초 실행시 오늘 날짜의 일정을 보여주기 위해 오늘 날짜 획득, 그 후 FileManager가 일정 파일 경로 설정을 위해 날짜 정보 확인시 참조됨
*/
void Date::setToCurrentDate()
{
    QDate current_date = QDate::currentDate();
    setDate(current_date);
}

/* setToSpecificDate()
- Q_INVOKABLE 함수
용도 : 사용자가 다른 날짜의 일정을 관리하길 원할 때 해당 날짜로 설정
시퀀스 : 사용자가 qml에서 날짜 변경시 호출되어 날짜 정보 변경, 변경 과정에서 setDate()에 의해 signal-slot 작업 수행
*/
void Date::setToSpecificDate(int y, int m, int d)
{
    QDate specific_date(y, m, d);
    setDate(specific_date);
}

/* getYear(), getMonth(), getDay(), getDayOfWeek()
용도 : 현재 Date객체가 저장하고 있는 날짜정보 반환
시퀀스 : FileManager가 일정파일 경로를 설정할 때 호출되어 값을 반환
*/
int Date::getYear() const { return year; }
int Date::getMonth() const { return month; }
int Date::getDay() const { return day; }
int Date::getDayOfWeek() const { return day_of_week; }
