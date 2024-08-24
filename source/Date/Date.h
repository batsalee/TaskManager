/* Date 클래스

1. 클래스 관계
FileManager 클래스에 날짜정보 제공
qml과 직접적으로 소통하는 클래스

2. 용도
프로그램이 현재 관리중인 스케쥴의 날짜 정보를 저장 및 관리하는 클래스
- 프로그램 최초 실행시 오늘의 날짜 획득
- 사용자에 의해 날짜 변경시 해당 날짜 정보 기록

3. 구현방식
싱글턴 패턴으로 구현
이유 1) 하나만 있으면 된다는 점
이유 2) qml과 integration
이유 3) FileManager에서 날짜기반 경로 설정 시 참조목적으로 전역접근

4. 고민
1) chrono 라이브러리를 써먹으면 더 좋지 않을까 생각 중, qml 시간정보 표시도 그렇고 추후 알람 기능 구현시에도 더 유용할것으로 예상 중
2) setDate()에 공통부분 작성 후 두 함수에서 호출이 아니라, 템플릿 메서드화 하는 방법도 있음
   하지만 문제는 setToSpecificDate는 사용 빈도가 setToCurrentDate에 비해 훨씬 낮을걸로 예상되며, 대부분의 경우 프로그램 실행 내내 한번도 사용되지 않을 가능성이 높음
   만약 이걸 C++ 내에서만 처리한다면 게으른 초기화를 사용하면 되겠지만, qml과 integration해야 하므로 프로그램 거의 시작과 동시에 객체를 생성해야 하니 비효율이 발생함
   그러므로 클래스 분리보다는 공통 부분을 함수로 묶고 호출하는 식으로 구현하기로 함
*/

#pragma once

#include <QObject>
#include <QDate>

class Date : public QObject
{
    Q_OBJECT

private:
    int year;
    int month;
    int day;
    int day_of_week; // 요일별 할일 기능을 사용하기 위해 오늘이 무슨 요일인지 알아야 함

    Date(); // 객체 사용 실수를 방지하기 위해 생성시점에 오늘의 날짜로 정보 설정
    virtual ~Date() = default;

    // 싱글턴 구현 위해 복사, 이동, 대입 delete
    Date(const Date& d) = delete;
    Date(Date&& d) = delete;
    Date& operator=(const Date & d) = delete;

    // setter
    void setDate(QDate& q_date); // 아래 public의 setToCurrentDate()와 setToSpecificDate()의 코드 중복부분 작성

public:
    static Date& instance(); // 싱글턴 객체 획득 함수

    // getter
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    int getDayOfWeek() const;

    // setter
    void setToCurrentDate(); // 날짜 정보 오늘 날짜로 설정
    Q_INVOKABLE void setToSpecificDate(int y, int m, int d); // 날짜 정보 사용자에 의해 특정 날짜로 설정

signals:
    void dateChanged();
    void readyToLoad();
};
