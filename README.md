# \[리팩토링\] TaskManager

## 목차
1. 개요
2. 개선 예정 사항
3. Class Diagram
4. 계획
5. 진행상황

___
## 1. 개요

아래 링크의 TaskManager 프로젝트를 진행하면서 소규모지만 release해볼 기회가 있었습니다. 이 때 받은 피드백들과 직접 사용하면서 느낀 불편한점들을 개선하기 위해 몇몇 기능을 기능을 추가/수정했었습니다.  

하지만 기능을 추가하고 수정할수록 코드는 점점 복잡해져갔고 단순히 기능을 나누는 모듈화만으로는 한계가 있다고 생각됐습니다. 그래서 전부터 꼭 공부하고 싶었던 디자인패턴을 학습하게 되었습니다. 이를 통해 배운점들을 반영해서 기존의 프로그램을 리팩토링하고, 동시에 기능을 추가하고 개선해나가고자 합니다.

https://github.com/batsalee/TaskManager/tree/version-1.0-backup

---
## 2. 개선 예정 사항

감사하게도 사용자분들에게 피드백을 받을 수 있었고, 저 또한 오랫동안 이 프로그램을 사용해왔기에 개선해야 할 점을 많이 느껴왔습니다. 이 탭에는 개선해야 할 일들의 리스트를 작성해두고자 합니다.  

#### 개발 환경
1) 컴파일 시스템 QMake에서 CMake로 변경  
- QMake는 Qt만을 위한 빌드 시스템이라면 CMake는 더 범용적인 시스템이며 더 최신식으로 권장됨  
- version 1.0은 QMake였지만 version 2.0은 CMake를 사용해보기로 결정

#### 기존 기능 개선
1) Task 추가 옆으로도 가능하도록 **기능추가**, qml에서의 수정이 우선적으로 필요함
2) Task 추가시 리스트의 제일 아래가 아닌 제일 위에 추가되도록 **변경**
3) Task 변경시 모달에 원래의 내용이 뜨도록 **기능개선**
4) 중요도가 높아서 ★로 표기한 Task는 하루가 지나도 빨갛게 변하지 않도록 **기능개선**
5) main Window의 크기를 고정하지 않고 직전 종료시의 Window의 크기와 위치를 유지하도록 **기능추가**

#### 신규 기능 추가 및 개선
1) 리팩토링
  - 단일책임원칙 준수하도록 Scheduler 클래스 분리
  - Scheduler 클래스를 Scheduler/FileManager/JsonManager 클래스로 분리
  - 또한 단일책임원칙 및 의존역전원칙 준수를 위해 계층화 및 상속구조 구현
  - 인터프리터 패턴을 위해 클래스를 직접 구현해서 분리할지, 아니면 시간정보등을 깔끔하게 저장하기 위해 json을 채택할지에  대한 고민

2) 알람기능 추가
  - 이건 좀 도전적인 과제인데 알람 기능을 추가하기 위해 필요한 기능은 다음과 같음
  - 알람을 울리기 위해 소리가 나게 하거나 창이 팝업되어야 함
  - Task정보에 시간정보가 포함되어야 함, 이를 위해 기존의 일정파일 save방식을 모두 변경해야 함, 또한 일정파일을 읽어왔을때  시간정보가 등록되어 있는 Task가 있다면 이를 처리하기 위한 신규 클래스가 필요함
  - 이 과정에서 신규 클래스의 상속관계 계층화나 클래스 분리를 어떻게 해야할지 모르겠어서 디자인 패턴을 공부했던 계기가 되었음

3) 초기 설정 창 추가
  - 기존에는 txt파일에 직접 입력하는 식이었지만 이젠 프로그램에서 자체적으로 지원하도록 변경해줘야 할 때가 되었음

4) 위의 3번에 이어서 다른 날짜에 대한 일정 추가도 프로그램 내에서 지원하도록 구현

5) 코드 정리, 함수에 const들도 좀 붙이고 예외 처리 필요한 곳들 처리해주기

---
## 3. Class Diagram

구현 목표를 미리 충분히 기획한 후 전체 구조를 정해두고 시작할까 합니다.  
실제로 구현하다보면 처음 다뤄보는 내용들에서 구조 변화가 다소 생길 수 있지만 전체적인 틀이 변하지는 않을 듯 합니다.  
![](https://blog.kakaocdn.net/dn/bs4xPu/btsIy2N5JqI/k7IlbOu3lC1SFtwE0HBPZK/img.png)
````
```mermaid
classDiagram
    class FileManager{
        -file_path : QString
    }
    class FileReader{
        -readTaskfile() JSON
    }
    class FileWriter{
        -writeTaskfile() JSON
    }
    FileManager<|--FileReader
    FileManager<|--FileWriter

    class JsonManager{
        json : string
        task_list : QList~QList~string~~
    }
    class JsonParser{
        +makeList(fr : FileReader) QList~QList~string~~
    }
    class JsonMaker{
        +makeJson(fw : FileWrite) JSON
    }
    JsonManager<|--JsonParser
    JsonManager<|--JsonMaker

    FileManager<..JsonManager

    class Schedule{
        -task_list : QList~QList~string~~
        -appendDayOfWeekTaskfile() : void
        -appendYesterDayTaskfile() : void
    }
    JsonManager--Schedule

    class Alarm {
        alarms : Priority_Queue~timeData, string~        
    }
    JsonManager--Alarm

    class ScheduleMaker {        
        schedule_text : QString
    }
    class InitialSchedule{
        -initialTaskfile() : void
    }
    class ModifySchedule{
        -updateTaskfile() : void
    }
    ScheduleMaker<|--InitialSchedule
    ScheduleMaker<|--ModifySchedule

    ScheduleMaker--JsonManager

    class FolderOpener {
        -file_path : QString
        +openFolder(file_path : const QString&) void
    }

    class Date {
        -year : QString
        -month : QString
        -day : QString
        -day_of_week : QString
        -getTodayDate() void
    }
    FileManager-->Date
```
````

#### 각 클래스에 대한 설명
1) Class JsonManager  
- json 라이브러리 헤더 추가
- json파일의 내용과 이중리스트 내용을 보관할 멤버변수 보유  
- JsonParser 클래스와 JsonWriter 클래스의 부모클래스  
  
	1-1) Class JsonParser  
	- json to 이중리스트 파싱  
	- 스케쥴은 이중리스트에 넣음  
	- 알람정보가 있는 스케쥴은 따로 등록  
  
	1-2) Class JsonMaker  
	- 이중리스트 to json 파싱  
  
>[!note]
>json을 처음다뤄보는거라 변수가 많지만   
>만약 배열구조로 저장할 수 있다면 스케쥴만 배열로 저장하고  
>알람은 따로 객체로 저장하고  
>고정일정(매년 특정날, 매월 특정날)도 따로 객체로 지정할 수 있다면 정말 편하지 않을까 예상중입니다.  
  
2) Class FileManager  
- 파일입출력 관리자의 역할  
- File 경로를 멤버변수로 가짐  
- FileReader 클래스와 FileWriter 클래스의 부모클래스  
  
	2-1) Class FileReader  
	- 싱글턴  
	- 필요한 스케쥴 파일의 내용을 read  
	  
	2-2) Class FileWriter  
	- 싱글턴  
	- JsonMaker에 의해 작성된 내용을 파일에 write  
  
3) Class Schedule  
- 이중리스트 관리자  
- 이중리스트 내에 내용 Insert/Update/Delete 담당  
  
4) Class Alarm  
- 싱글턴  
- 등록된 알람을 우선순위큐에 push  
- 우선순위큐에서 앞에꺼부터 알람 타이밍 되면 알람 보내도록  
- 알람기능 구현이 문제  

5) Class ScheduleMaker  
- version 1.0에서는 FolderOpener가 폴더를 열고 사용자가 직접 파일의 내용을 수정했었음  
- 해당 기능을 프로그램 내에서 수정 가능하도록 구현  
- 내용 입력할 창을 만들고, 입력된 내용을 JsonMaker가 json으로 만들고 FileWriter가 파일로 저장한다.  
- 템플릿메서드 내지는 스트래티지로 뭘 열지, 어디에 저장할지는 하위클래스에서 구현  
- InitialSchedule 클래스와 ModifySchedule 클래스의 부모클래스  
  
	5-1) Class InitialSchedule  
	- 프로그램을 처음 설치시 초기설정을 위한 기능 구현  
	- everyday부터 월~일의 내용 적용  
	  
	5-2) Class ModifySchedule  
	- 이미 작성된 스케쥴을 수정하거나 새로운 스케쥴을 사전에 추가할때 사용  
  
6) Class FolderOpener  
- version 1.0에서의 FolderOpener의 일부 기능은 ScheduleMaker 클래스로 넘어갔음  
- 하지만 여전히 자료들 넣는 폴더 켜주는 기능은 유용하므로 클래스 유지  
  
7) Class Date  
- 날짜 관리 클래스  
- version 1.0의 Date 클래스에서 큰 변동은 없음

---
## 4. 계획

한동안은 기존에 공부했던 모든 내용들을 복습하면서 남는시간엔 이 프로젝트를 진행할듯합니다.  
진행 순서를 기록해두고 보면서 진행해볼까 합니다.  

#### 1) json에 대한 이해
- json 라이브러리 선택
- 현재 원하는 사용 구조는 task들은 배열의 형태로 원본 그대로 저장하고, 알람은 알람 객체로 저장하고, 고정일정은 고정일정 객체로 저장하는 구조
- 위 구조가 실현 가능한지 파악 후 조정해야할 점이 있다면 조정

#### 2) FolderOpener 클래스와 Date 클래스 구현
쉽게 구현이 가능하면서도 FileManager 클래스가 없을때 직접 파일을 조정하기 편하도록 우선으로 구현합니다.  
또한 Date클래스는 FileManager 클래스의 선행클래스이므로 우선 구현합니다.  

#### 3) FileManager 클래스 구현
json으로 원하는 저장구조와 이중리스트 구현 구조를 갖췄다면 해당 내용을 파일에 잘 저장하도록 구현합니다.  

#### 4) Schedule 클래스 구현
Schedule 클래스는 이미 version 1.0에서 잘 작동하고 있었으나 일부 기능을 위의 1, 2번탭의 내용으로 이전하므로 해당 부분에 대한 수정만 이루어지면 될 듯 합니다.  
여기까지 마친다면 클래스 구조적인 리팩토링 및 저장구조 개선은 끝이라고 볼 수 있을 듯 합니다.  

#### 5) Alarm 클래스 구현
여기서부터는 도전적인 내용이며 새로 추가되는 기능입니다.  
알람 구현에 대해 조사해보고 구현해볼까 합니다.  

#### 6) ScheduleMaker 클래스 구현
일정 파일을 직접 조작하는것이 아닌 프로그램 내에서 작성 및 수정 가능하도록 구현해보고자 합니다.  

---
## 5. 진행상황

#### 2024-07-14
11:03 문서 작성 최종 완성  
13:39 CMake 기반 프로젝트 생성 및 ReadMe.md 작성  

#### 2024-07-18
16:25  
json 라이브러리 선정 완료  
C++에서 json 사용하게 해주는 라이브러리는 RapidJson과 nlohmann 두개정도가 대표적인듯 했다.  
이 중 대략적으로 스타일 보고 자료양봤을때 RapidJson쓰면 무난할듯 해서 RapidJson으로 선택 완료  
그 후 GitHub에서 라이브러리 다운 받아서 프로젝트 폴더에 넣은 후 CMakeList에 반영했다.  

19:40  
리팩토링 시작 및 기능 구현 시작  
오늘은 우선 3가지 기능정도만 구현하면서 클래스 분리했다.  
1) FileManager, FileReader 클래스 : ifstream에서 스트림만 획득하게 했다.  그 후 해당 내용을 string에 담는다.
2) JsonManager, JsonParser 클래스 : string에 담긴 내용을 json 형식으로 파싱한다. 그 후 결과 내용을 Document에 담는다.
3) Schedule 클래스 : Document의 내용을 Schedule 클래스 멤버변수인 이중리스트에 담는다. 이제 Schedule 클래스는 이중리스트 관리자 역할만 한다.  

가) 고충과 해결방법  
(1) 좀 당황스러운게 github 브랜치에다가 커밋하면 잔디가 안깔린다...?  
어차피 수정내역 옵시디언에 남겨서 그걸로 깔리긴 하겠지만 이거때문에 또 빼먹을수도 있으니 조심해야할듯하다...  
(2) Qt Creator 인코딩 문제  
Qt Creator 문제라고 봐야할듯한데 기본 인코딩이 UTF-8로 되어있었다. json도 기본적으로 UTF-8 인코딩이라고 하길래 이러면 따로 인코딩 없이 잘 호환 될거라고 생각해서 그대로 쓰려고 했었다.  
근데 문제는 cout이나 cerr로 한글 출력하면 한글이 다 깨져버렸다. 이게 왜 이런지 한참 찾다가 결국 EUC-KR로 변경하고나서 잘 출력됐다. 결국 json에서 Qt로 올때는 또 EUC-KR로 인코딩 해야할듯하다.  
(3) 파일 경로 설정  
Schedule이 담겨있는 json파일을 어디에 둬야할지 좀 헤맸다.  
일단 상대경로를 작성해야 하는데 실행파일 혹은 main.cpp 둘 중 하나일테니 둘 다 해봤는데 안됐다...  
아무리 해봐도 안되서 version 1.0꺼 봤는데 이상하게 현재폴더에 하위폴더로 두고 했길래 보니까 Qt Creator는 빌드를 프로젝트 폴더 내에 Debug 폴더를 만들고 그 안에서 하는걸 확인했다. 그래서 해당 실행파일로부터의 상대경로로 설정하니까 잘 됐다.  

나) 다음 계획  
다음 계획은 qml쪽 포팅해서 이중리스트 내용 qml에 보이게 만드는것부터 시작해야겠다.  
그래야 qml에서 지웠을때 이중리스트에도 반영되게 하는 등 사용할 수 있으니 qml부터 간다.  
알고리즘 공부만 하다가 리팩토링이랑 기능개선 추가 같이 하니까 좀 재밌는것같다.  

#### 2024-07-19
우선 version 1.0에서 작성해뒀던 qml 파일들을 그대로 옮겨줬다.  
근데 이 작업이 3시간쯤 걸렸다...  
그냥 옮기고 CMakeLists.txt에 등록해주면 끝일줄 알았다.  
하지만 아니었다.  

가) 고충과 해결방법  
(1) 프로젝트의 qml인식과 오류해결  
막상 qml들을 옮겨주고 실행해보니 main.qml에서 불러오는 내가 만든 다른 qml들을 인식을 못했고  
version1.0에서도 이런 경험이 있었는데 QMake파일을 빌드해주면 해결이 됐었다.  

근데 문제는 난 지금 CMake로 빌드하고 있고 아무리 찾아봐도 CMake 빌드라는 기능은 없었고  
전체 프로젝트 빌드도 해보고 구글링도 해보고 gpt한테도 물어보고 해도 뭘 해도 다 인식이 안됐다.  

구글링할때 많은 해결법들이 CMakeLists.txt 파일에 qt_add_qml_module 이라는 내용을 수정해주라고 했었다.  
근데 내 CMakeLists.txt에는 qt_add_qml_module옵션이 있지도 않았고, 그래서 직접 작성해서 추가해주면 프로그램이 실행조차 안됐었다.  

결국 이렇게 3시간쯤 흐르다가 문득 프로젝트 파일에 뭔가 필요없어 보이는 폴더들이 많아서 하나하나 확인해봤고 거기서 해결법을 찾았다.  
프로젝트 자체 파일 중 구석에 있는 파일하나에 qt_add_qml_module라는 옵션이 있었고 거기에 내가 추가한 qml들을 나열해주니 인식이 됐다.....  프로젝트 루트경로에 있는 CMakeLists.txt가 아닌 서브폴더에 있는 qmlModule이라는 파일이었다.  
왜 이게 숨어있어서 이렇게 시간을 낭비하게 하는건지, 또 qml을 추가하면 자동으로 저기에 내용을 추가해줘야지 왜 이걸 직접 해야하는지도 이해가 안된다...  

아무튼 위 옵션에 내가 추가한 qml들을 나열하고 실행해보니 실행이 잘 됐고 아직 구현이 완벽하지 않아서 안뜨는 내용들도 있었지만 시계나 버튼등은 일단 확실히 제 위치에 뜨는걸 확인했다.  

(2) 근데도 오류는 남아있다.  
위 설정을 마친 후 실행이 잘 되고 qml이 화면에 잘 뜨기까지 했다.  
근데 코드에는 오류가 있다고 떴다.  
오류 내용은 Unknown component. (M300) 였고 관련해서 검색해보니 비슷한 오류를 겪는 사람이 아주 많았는데 일단 상대경로를 import해주는 방법으로 해결했다.  
main.qml에 import "./qml"를 추가해줬는데 이게 제대로 된 해결법인진 모르겠다. 일단 경로 지정해서 qml 파일을 인식했으니 오류가 사라진거같긴한데 QMake때는 저런거 없이도 잘 됐어서 왠지 다른 프로젝트 파일에 설정해주는게 더 권장되는 방법이 아닐까 싶어서 찝찝하다.  

나) 다음 계획  
일단 어찌됐든 qml도 포팅해줬으니 다음 목표는 Schedule 객체가 관리하는 이중리스트와 qml의 taskList간의 연동이다.  
둘이 연동이 되야 일단 내용이 잘 왔는지, 잘 지워지고 있는지 확인이 가능하므로  

#### 2024-07-22
16:51  
Schedule클래스의 scheduler 객체와 qml간의 integration 완료  

이건 version 1.0부터 integration하는 방법이 너무 여러종류가 뭘 써야하는지 도저히 몰라서 이것저것 썼었는데 여기서부턴 Q_PROPERTY로 통합해서 작성하는걸로 결정  
```C++
#include <QObject>

class Schedule : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QList<QString>> schedule_list READ GetScheduleList NOTIFY ListChanged)
...

signals:
    void ListChanged();
}
```
위처럼 QObject 상속받고, Q_OBJECT매크로 걸어주고, Q_PROPERTY에 내용 나열해주면 된다.  

Q_PROPERTY에 대한 설명을 남겨두자면  
1) 첫번째에 있는 schedule_list는 qml쪽에서 접근할 이름을 지정해준 것
2) READ에 작성하는 함수는 qml에서 schedule_list이라는 이름으로 접근시 어떤 함수를 사용하면 될지 지정
3) WRITE함수도 작성할 수 있는데 여기선 안했는데 이건 qml에서 schedule_list라는 이름으로 뭔가 변경했을때 어떤 함수가 해당 내용을 반영할지 지정
4) NOTIFY는 변경이 발생했을때 일으킬 signal을 지정, 주로 WRITE함수쪽에서 변경 후 emit으로 시그널 발생

여기까지 완성 후 qml쪽에 내용이 뜨는것까지 확인 완료  
![](https://blog.kakaocdn.net/dn/w1NsM/btsII0o7mOI/6KHlgS2me1gIYvKQDUi840/img.png)
근데 뭔가 줄간격이나 버튼 모양같은게 version1.0 qml을 그대로 가져온건데도 조금씩 달라져있어서 해당 부분은 나중에 기능조정 후에 디자인 조정좀 해야할것같음  

20:02  
Schedule 클래스의 insertTask, updateTask, deleteTask함수 구현 및 qml과 연동 완료  
값 변경을 위해 우클릭시 기존의 값이 뜨도록 qml 구조 변경  
  
새로 발생한 고민  
기존엔 할일 문자열 자체에 #, @, ★을 포함시켜서 일의 중요도를 표시했었음  
근데 지금 json 배열로 사용하려고 보니 해당 중요도를 포함시킬 방법이 없는 상황  
그래서 결국 json 배열 구조를 배열안에 객체가 들어가게 해서 객체가 중요도를 포함하게 할지 고민중  
혹은 문자열 자체에 포함시키는것도 방법인데 기존에 C#같은걸 입력하려면 \#때문에 문제가 됐어서 제약이 좀 있음  
