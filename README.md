# \[리팩토링\] TaskManager

## 목차
1. 프로그램 소개
2. 프로젝트 개요
3. 리팩토링 계기
4. 프로젝트 구성
5. 고충 및 해결방법
6. 향후 계획
7. 사용된 기술
8. 링크

___
## 1. 프로그램 소개

해야할 일(Task)들을 관리하는(Manage) 프로그램이라는 뜻입니다.  
To-do List를 자동화하여 관리하는 프로그램입니다.  

![](https://blog.kakaocdn.net/dn/baMZwZ/btsJhkgeXeh/67FtATApuUfM9BCqg24kjk/img.png)

___
## 2. 프로젝트 개요

#### 1) Task 리스트 자동 생성
- **매일 해결해야 할 일**들의 리스트를 자동으로 나열해줍니다.  
- **요일별 해결해야 할 일**들의 리스트 또한 자동으로 추가됩니다.  
- **지난날 해결하지 않고 미루어둔 일**들의 리스트 또한 자동으로 추가됩니다.

#### 2) 간편한 사용법
- 나열되어 있는 일들 중 해결한 일은 더블클릭으로 목록에서 **제거**할 수 있습니다.  
- 해야할 일을 변경해야 한다면 우클릭으로 간단히 내용을 **변경**할 수 있습니다.  
- 기존 일정 외에 해야할 일이 더 생긴다면 내용을 **추가**할 수 있습니다.  
- 특정 날짜에 해야할 일정을 미리 추가해둔다면 해당 날짜에 리스트에 반영됩니다.

#### 3) 시각적 효과
- 중요도에 따라 일의 목록을 다르게 나타냅니다.  
- 기본적인 일은 **푸른 배경**에 흰 글씨로 나타냅니다.  
- 중요도가 높은 일은 **검은 배경**에 금색 글씨로 나타냅니다.  
- 지난날에 해결하지 않고 미뤄둔 일들은 **붉은 배경**에 회색 글씨로 나타냅니다.

#### 4) 인터페이스 구성
- 시간과 날짜가 표시됩니다.  
- 해야할 일들의 리스트가 나열됩니다. 리스트가 많다면 스크롤을 하거나 창의 크기를 조절할 수 있습니다.  
- 버튼을 이용해 할일을 추가하거나 일정을 관리하는 등의 기능도 수행할 수 있습니다.

---

## 3. 리팩토링 계기

이 프로젝트는 최초에는 개인적으로 사용하기 위해 만들었던 프로젝트였습니다.  
그렇기에 프로그램의 구조화, 확장성, 사용편의성보다는 빠른 개발에 초점을 두고 진행했었습니다.  

다만, 이 프로그램을 당시 공통 관심사를 가진 그룹에 공유하게 되었고 사용자들에게 피드백을 받아 기능개선 및 기능추가 작업을 하게 되었습니다.  
그 과정에서 구조화되지 않은 프로젝트에 기능을 더할수록 코드는 더욱 복잡해지고 기능확장에도 한계를 느끼게 되었습니다.  
그래서 디자인패턴 및 소프트웨어공학적인 측면에서의 객체지향의 개념에 대해 다시한번 공부하게 되었고 해당 내용들을 반영하고 사용해보기 위해 이 프로젝트의 전체적인 구조를 리팩토링하게 되었습니다.  

또한 최초의 구조에서는 파일을 파싱하는 인터프리터 함수를 사용했었는데, 이 함수에서 특정한 문자들을 렉싱요소로 뒀기에 사용자가 해당 문자들을 사용할 수 없는 상황이었습니다.  
그래서 파일 저장 구조를 json으로 변경하고 rapidjson을 적용한 인터프리터 클래스를 구성하는것이 또 하나의 이유가 되었습니다.  

리팩토링 전의 version 1.0 프로젝트 내용은 아래의 링크에 기록해뒀습니다.  
https://smallpants.tistory.com/270

---
## 4. 프로젝트 구성

#### 1) 리팩토링 전
먼저 최초 개발 후 사용자 피드백에 따라 기능개선 및 기능추가했던 version 1.0의 클래스 다이어그램입니다.  
![](https://blog.kakaocdn.net/dn/eACe4l/btsJgyGmOOh/6RLKZjJSEP59U7psCpEA01/img.png)

다음은 당시의 qml 모듈 다이어그램입니다.  
![](https://blog.kakaocdn.net/dn/20ROH/btsJhgEYwSy/K05k1qsxUrlhYwKQY5crHk/img.png)

개인적으로 사용하기 위해 만든 프로젝트인 만큼 구조가 간결했고, 그 구조에 각종 기능을 추가하다보니 클래스의 크기가 커지고 기능 발전의 한계를 느끼게 되었습니다.  

#### 2) 리팩토링 계획 단계
리팩토링을 앞두고 전체적인 프로그램의 구조를 정해두고 시작하고자 했었습니다. 기존 클래스의 분리 및 앞으로 기능발전을 염두해둔 구조로 구성하고자 했었습니다.  
하지만 막상 프로젝트를 진행하다보니 더 나은 구조가 떠오르거나 구조의 한계를 보게되었고 최초의 계획을 조금씩 변경하며 발전시켜갔습니다. 또한 클래스 구조가 계획과 달라지면서 기능 또한 달라졌기에 해당 상황에 더 잘어울리는 클래스 이름으로 변경하는 등의 변화가 생겼습니다.  
![](https://blog.kakaocdn.net/dn/mnAkK/btsJgKNnCHm/wRonsbAZBX4qME8UvxpFt1/img.png)

#### 3) 리팩토링 결과

클래스 다이어그램을 mermaid로 그리는데 한계를 느껴 아래는 draw.io를 활용했습니다.  
![](https://blog.kakaocdn.net/dn/AG4oH/btsJf98iklO/IKLvaPPauBiRXP9oD6zZ20/img.png)
![](https://blog.kakaocdn.net/dn/bhTCHP/btsJh7tXUnj/w320TkWFoiOTc8vuGdWkA1/img.png)

#### 4) 각 클래스에 대한 설명

① Alarm  
- 사용자가 등록한 알람에 대한 관리 및 알림 담당 클래스(향후 기능 추가시 반영 예정)

② FolderOpener  
- 일정 파일이 저장되는 경로 및 사용자 파일 경로를 윈도우 탐색기로 열어주는 클래스  
  
③ Tutorial  
- 최초 사용 방법 안내 및 고정일정 등록 담당 클래스

④ Date  
- 날짜 정보를 관리하는 클래스
- 프로그램 최초 실행시 오늘의 일정을 표시하기 위해 오늘의 날짜 획득
- 다른 날짜의 일정을 관리하기 위해 사용자 요청에 의해 날짜가 변경되면 해당 날짜의 일정을 불러오도록 시그널 발생

⑤ FileManager  
- 파일입출력 및 파일시스템 담당 클래스들의 부모클래스
- 파일의 경로에 대한 기능 담당

⑥ FileReader  
- 파일을 읽어오는 클래스
- FileManager 클래스의 자식클래스이며 파일의 내용을 읽어오는 기능을 확장

⑦ FileWriter
- 파일에 내용을 쓰는 클래스
- FileManager 클래스의 자식클래스이며 파일에 내용을 쓰는 기능을 확장

⑧ JsonManager
- 외부 라이브러리인 rapidjson을 받아오는 Json 관리 클래스들의 부모클래스
- 인터프리터 클래스

⑨ JsonParser
- json 문구를 파싱해서 프로그램에 필요한 형태로 변환하는 클래스
- JsonManager 클래스의 자식클래스이며 json문구를 파싱하는 기능을 확장

⑩ JsonSerializer
- 프로그램이 사용하던 데이터를 json문구로 변환하는 클래스
- JsonManager 클래스의 자식클래스이며 데이터를 json문구로 시리얼라이징하는 기능을 확장

⑪ ProgramInfo
- 프로그램의 정보를 관리하는 클래스
- 프로그램 최초 실행시 program_info.json 파일을 통해 튜토리얼 유무, 최근 실행된 날짜 등의 정보를 획득 및 관리

⑫ Task
- 일정 정보를 담는 구조체
- 일정의 내용을 담는 title과 일정의 중요도를 담는 importance로 구성

⑬ TaskListManager
- 이 프로그램의 핵심 클래스
- 사용자가 관리하는 일정들이 담긴 task_list(이중리스트)를 관리하는 클래스
- 이중리스트를 만들고, 불러오고, 저장하는 등 crud를 담당하는 클래스

---
## 5. 고충 및 해결방법

리팩토링 전 version 1.0 개발 중의 고충 내용은 아래 문서에 정리되어 있으며, 아래의 내용들은 리팩토링 과정에서의 생겼던 고충들과 해결해 나간 방법들에 대한 기록입니다.  
[https://smallpants.tistory.com/270](https://smallpants.tistory.com/270)

#### 1) GitHub branch
리팩토링은 git branch를 만들고 해당 브랜치에서 작업해서 push했었는데 GitHub contribution에 반영되지 않아서 당황스러웠습니다. 브랜치에 기여한 기록들은 해당 브랜치가 main브랜치에 merge될때 반영된다고 합니다.

#### 2) CMake 빌드 시스템
기존의 version 1.0은 Qt5에서 작업했기에 QMake 빌드 시스템을 사용했었습니다. 반면 리팩토링한 version 2.0에서는 Qt6에서 작업했고 CMake 빌드 시스템을 사용하게 되었습니다.  
지금까지 주로 Visual Studio에서 C++ 프로젝트를 해온 결과 Make 시스템에 대해 생각할 기회가 적었는데 오랜만에 리눅스에서 vim으로 작업하던 시절에 Makefile을 직접 만들고 make하던 기억을 떠올리는 계기가 됐습니다.  
다만 Qt Creator에서 처음 사용해보는 빌드 시스템인 만큼 파일 모듈화시 고충이 많았고 소스코드 뿐 아니라 qml 모듈화 시 경로설정 및 경로 작성 위치 등에 대해 파악하기 위해 하루를 소비하기도 했었습니다.  
주로 문제점은 소스파일의 경로를 작성하는 CMakeLists.txt 파일과, qml의 경로를 작성하는 qmlmodules 파일이 구분되어 있다는 점이었고 이에 대한 내용은 youtube에서 qt 공식 안내 영상을 본 후 파악했고 파악한 이후는 편리하게 사용이 가능해졌습니다.  

#### 3) json 라이브러리
기존의 version 1.0에서는 빠른 사용을 위해 메모장에 해시태그로 Task를 분리해서 작성 가능하도록 구현했었고, 이를 파싱하는 함수를 통해 내용을 해석했었습니다. 다만 해시태그 문자인 \#이 렉싱요소가 되면서 C\#같은 문구를 일정에 넣을 수 없었습니다.  
이런 문제를 해결하기 위한 아이디어로 디자인 패턴을 공부하던 중 프로토타입 패턴에서 데이터 저장 구조에 대해 다룬 내용을 떠올리게 되었고 json과 xml 형식 중 적합한 저장형식을 고민하게 되었습니다. 일정 내용을 배열형태로 저장하는 빈도가 많은 만큼 xml보다는 배열구조 저장에 유리한 json을 선택하게 되었습니다.  
c++에서 json을 사용할 수 있게 해주는 라이브러리는 RapidJson과 nlohmann 두 라이브러리가 대표적인듯 했고 예시 자료가 더 풍부했던 RapidJson을 선택해서 반영하게 되었습니다.  
해당 라이브러리를 활용하는 인터프리터 클래스 구현에 큰 도움이 되었고 파일 저장 구조에서도 많은 이점을 얻게 되었습니다.  

#### 4) 인코딩 문제
version 1.0에서도 그랬지만 인코딩 문제는 번거로운 일인듯 합니다. Qt Creator의 GUI 출력부는 UTF-8로 인코딩되며, json도 기본적으로 UTF-8로 인코딩된다고 합니다. 그래서 json 내용을 GUI로 표현할땐 인코딩 문제가 없었습니다.  
하지만 관련 내용을 디버깅하기 위해 콘솔에 출력하면 한글이 모두 깨져서 출력됐고 이때문에 다소 시간을 소비했습니다.  
해결방법은 결국 콘솔 출력 방식을 EUC-KR로 변경하면 됐고, json에서 읽어온 내용은 UTF-8이므로 QString에 담아 출력하도록 사용했습니다.

#### 5) qml과 c++의 integration
version 1.0에서는 일정 파일이 담긴 이중리스트에 변화가 생길 때 마다 시그널을 발생시키고, qml의 Connections을 통해 갱신하게 만들었었습니다.  
다만 좀 더 Qt에서 권장되는 Q_PROPERTY를 사용해보고 싶었고 이를 이용하도록 변경했습니다.  
그 결과 기존에는 변경이 생길때마다 내용 전체를 직접 갱신해야 했지만, 변경후에는 프레임워크에 의해 자연스럽게 관리되도록 변경됐습니다.

#### 6) Qt Quick 버전 문제
version 1.0은 Qt 5에서 작업을 했고 이때 당시 Qt Quick의 최신버전은 2.15였다고 합니다. 다만 리팩토링은 Qt 6에서 작업을 하게 되었고 Qt 6에서는 Qt Quick이 6.x버전으로 업그레이드 되었다고 합니다.  
이로인해 같은 qml 파일을 가져와서 사용했음에도 차이가 발생하게 되었고 이에 따라 각 타입의 크기를 조정해야 했습니다. 타입의 크기 외에도 qml쪽에서 발생하는 문제를 javascript로 해결해뒀었는데 해당 기능이 더이상 작동하지 않게되어 문제점으로 남아있습니다.  

#### 7) Two Hats
리팩토링 관련 용어로 Two Hats라는 말이 있는데 기능추가와 리팩토링은 분리되어야 한다는 뜻입니다. 즉 리팩토링은 기능추가를 위한것이 아니라 기존의 기능을 완벽하게 유지하되 더 좋은 구조로 변경하는 것이라는 뜻입니다.   
하지만 당시 일정 파일을 json을 통해 관리하게 만들면서 새로운 기능들을 추가하고 있었고 기능추가와 리팩토링을 혼합해서 진행하고 있었습니다. Two Hats라는 용어를 알게 된 후로 기능 추가는 모두 이후로 미뤄뒀고 리팩토링에만 집중하게 되었습니다.  

#### 8) 단일 책임 원칙
리팩토링을 하면서 항상 객체지향의 SOLID 원칙을 준수하기 위해 노력했습니다. 다만 단일 책임 원칙을 어느 수준까지 준수해야 하는지에 대해 고민을 했었습니다.  
고민은 "파일관리 클래스가 파일열기, 파일읽기, 파일쓰기, 파일닫기 4개의 기능을 담당한다면 이는 하나의 책임을 담당한다고 할 수 있을까?"에서 시작되었습니다. 최소한 파일열기, 파일닫기와 파일읽기, 파일쓰기는 분리되어야 하는것이 아닌가? 근데 그렇게 분리하고 나서 파일 열기와 닫기는 정 반대의 기능인데 하나의 클래스에 위치해도 괜찮은 것인가? 등의 고민을 하게 되었습니다. 결국 고민의 끝에서는 이런식으로 엄격하게 단일책임원칙을 준수한다면 결국 하나의 클래스는 하나의 함수밖에 갖지 못하게 될것이라고 결론내렸습니다.  
조사를 거친 결과 단일 책임 원칙 준수는 "클래스의 내용을 변경해야 한다면 그 이유가 하나여야한다."라는것이 핵심임을 이해하고 클래스 분리의 수준을 정할 수 있었습니다.  

#### 9) 클래스간의 커플링
단일 책임 원칙에 대한 고민에 이어 클래스간의 커플링에 대해 오랜 고민을 했습니다. 디자인패턴을 공부하며 배운 가장 큰 깨달음은 클래스간의 커플링을 줄이고 단일책임원칙과 개방폐쇄원칙을 준수하기 좋은 구조에 대한것이었습니다.  
이를 위해 클래스의 결과를 클래스가 받는것이 아니라 한 클래스는 데이터를 리턴하고 다른 클래스는 해당 데이터를 이용하는 방식으로 분리를 하고 이 과정을 절차지향적으로 구성하게 되었습니다.  
하지만 아무리 커플링을 줄이려고 해도 결국 프로젝트 내에서 만든 클래스들은 프로젝트에서 부품으로 사용하기 위함인데 각 부품이 전혀 결합되지 않는다는 것은 불가능했기에 커플링에 대한 고민과 조사를 많이 하게 됐고 약간의 커플링으로 코드 구성이 간소화된다면 차라리 약간의 커플링을 택하는게 맞다고 결론지었습니다.  
하지만 최대한 각 클래스간의 커플링을 줄이고 싶었기에 단 하나의 클래스인 TaskListManager를 모든 커플링의 중심이 되게 하고 나머지 클래스간에는 전혀 접점이 없도록 구현했습니다.

#### 10) 디자인패턴 vs 프레임워크
리팩토링을 시작하게된 주 목적 중 하나는 공부했던 디자인패턴을 적용해보기 위함이었습니다. 그래서 각 클래스들을 구성할때 적용할만한 디자인패턴이 있을지 고민하게 되었고 처음 2주정도의 작업물에는 팩토리메서드 패턴/싱글턴 패턴/비지터 패턴이 적용되어 있었습니다.  
하지만 해당 기능들의 대부분은 프레임워크에서 제공해주는 기능 한두줄로 모두 대체 가능했습니다. 이를 알고 있음에도 프레임워크에 의존하는것이 옳은가 vs 디자인패턴으로 표준화해서 작성하는것이 옳은가에 대한 고민을 오랜시간 하게 되었습니다.  
그 결과 프레임워크를 사용하는 이유가 내부 로직에대해 자세히 몰라도 간편하게 기능을 사용할 수 있다는 점인데 이를 사용하지 않으면 프레임워크를 사용하는 의미가 없다라고 판단해서 복잡한 디자인패턴 구성을 모두 삭제하고 Qt의 signal slot 기능을 이용하도록 변경했습니다. 근거로는 signal slot 구조가 옵저버 패턴과 다를바가 없다고 생각했기 때문에 이 또한 디자인패턴의 적용일 수 있다라고 생각했기 때문입니다.  
또한 프레임워크 뿐 아니라 라이브러리의 발전으로 내가 구현해뒀던 많은 코드들이 한줄만에 처리 가능해지는 상황이 온다면 그 기능을 사용하는것이 옳은가, 혹은 내 코드를 유지하는 것이 옳은가에 대한 고민도 해보게 되었습니다.  
만약 그 기능을 사용한다면 해당 기능을 바로 사용할지, 해당 기능을 리턴하는 래퍼형태로 써야할지 등에 대해 고민하면서 라이브러리나 프레임워크에 종속시키되 내 역할을 줄이는것이 맞는가 vs 툴은 툴일뿐 내가 작성하는것이 핵심이어야 하는가에 대한 고민을 하는 계기가 되었습니다.  

#### 11) 초기 계획과 달라진 진행상황
리팩토링을 진행하기 앞서 클래스 구조 및 관계를 설계해두고 시작하기 위해 클래스 다이어그램을 작성했었습니다.  
하지만 기존의 클래스가 분리되고 이를 연결해주기 위한 기능들을 추가로 구현하다보니 변경된 클래스의 용도에 더 적합한 이름으로 변경하고, 클래스들의 관계를 더 적합한 구조로 변경해나가게 되었습니다. 결국 초기의 계획과는 다소 다른 모습으로 마무리하게 되었습니다.  
UML을 공부하던 시절 현업에서는 클래스 다이어그램을 개발 시작시점이 아닌 개발을 마친 후 문서화가 필요할 떄 작성한다라는 말을 본적이 있었습니다. 당시에는 프로젝트 기획 시점에 클래스 구조를 정해두고 시작하면 더 좋을거라고 판단했기에 이해가 되지 않았으나 현재에는 프로젝트를 진행하면서 구조를 변경해나가는 것은 피할 수 없다라고 생각하게 되었습니다. 이는 모듈화 과정에서 커플링을 줄이려면 클래스간의 관계로만 모든것을 표현할 수 없기 때문이 아닐까 싶습니다.

___
## 6. 향후 계획

기능 확장을 위한 모든 준비가 끝났기에 앞으로는 각종 기능확장을 하고싶습니다. 이미 테스트해둔 내용도 많이 있습니다.  
다만 가장 앞서 해야할 일은 기존에는 사용자가 파일을 직접 조작해서 일정파일을 관리하기 쉬웠으나, json 구조로 파일구조를 변경하게 되어 사용자가 직접 일정파일을 조작하기 복잡해졌습다. 그러므로 일정 파일을 관리하는 기능을 gui로 구현하는것이 최우선 과제가 될 듯 합니다.  

1) 일정파일 관리 기능 GUI에서 구현
2) Button 대신 ComboBox로 변경
3) GUI에서 Task swap 및 이동 관련 기능 구현

위 3가지 기능만 구현된다면 당당하게 쓸만한 프로그램이라고 말할 수 있지 않을까 싶습니다.

___
## 7. 사용된 기술

- Qt 6
- C++
- CMake
- rapidjson
인터페이스를 위해 Qt Quick의 qml을 사용했고, 내부 로직은 C++을 사용해 처리했습니다.

#### 해당 기술들을 사용한 이유

1) C++을 선택한 이유  
- 우선은 윈도우에서 사용할 프로그램이므로 C++을 선택했습니다.
- 개인 일정을 다루는 프로그램이므로 데이터베이스 서버에 업로드하기보다는 개인 PC내에서 **파일입출력**을 통해 빠르게 처리하고자 했습니다.

2) Qt Quick을 선택한 이유  
- Qml과 C++을 분리해서 디자인부분과 코드부분을 관리할 수 있었습니다.  
- 이미 잘 다루는 C++로 개발할 수 있기에 디자인 부분을 담당하는 qml만 배우면 된다는 점에서 부담이 적었습니다.  
- **크로스플랫폼** 개발을 경험해보고 싶어서 선택했습니다.

또한 윈도우 GUI 프로그램을 만들기 위한 플랫폼을 선택하기 위해 많은 정보조사를 했습니다만 아래의 환경들은 해당 이유로 선택지에서 제외되었습니다.
- Win32 Api 및 MFC : 성능 중시 분야를 제외하고는 신규 프로젝트보다는 유지보수에 사용되며, 현재는 다소 과거의 개발 환경으로 여겨지는듯 했습니다.  
- Electron : 실행환경에 거의 영향을 받지 않는다고 볼 수 있는 웹 기반 GUI를 표현한다는 장점이 있었지만 HTML, CSS, JavaScript를 익혀야하므로 현시점에 당장 만들어보기에는 학습량이 배보다 배꼽이 더 커질 수 있는 상황이었기에 다음 기회로 미뤄두기로 했습니다.  
- nana 및 WinUI3 : C++에는 익숙하지만 GUI 개발환경은 새로 익혀야 하는 입장에서 자료가 너무 적었기에 아쉽게도 후순위로 밀리게 되었습니다.  
- Winform 및 WPF : 윈도우 프로그램을 만들기에 아주 좋은 선택지였지만 C#은 기초문법정도만 공부했던 상황인지라 Electron과 마찬가지로 학습량의 벽이 있었고, 무엇보다 .NET 환경에서만 작동 가능하다는 점이 Qt의 크로스플랫폼에 밀렸습니다. 다만 WPF는 다음 학습목표로 두고 꼭 배워보고 싶은 목표가 되었습니다.

GUI에 대한 조사내용은 아래의 글에 정리해두었습니다.
https://smallpants.tistory.com/294

___
## 8. 링크

#### 1) GitHub
https://github.com/batsalee/TaskManager/tree/version-2.0-refactoring

#### 2) Blog
https://smallpants.tistory.com/321

#### 3) 진행상황에 대한 기록
아래 링크에 진행 상황을 기록해가며 작업했습니다.  
정리되어 있지 않은 내용이며 해당 내용들이 정리된 내용이 이 문서이지만 관련 문서이므로 링크만 남겨둡니다. 
https://smallpants.tistory.com/315
