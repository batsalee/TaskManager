/* FolderOpener.h

1. 클래스 관계
다른 클래스와는 상관관계 없이 qml에서 호출하면 지정된 폴더를 열어줌

2. 용도
지정된 경로의 폴더를 윈도우 탐색기로 열어줌, 개인이 자주 사용하는 파일들을 실행하기 편하도록 구현

3. 구현방식
qml의 버튼을 누르면 윈도우 내의 특정 폴더를 열어주도록 Q_INVOKABLE로 구현
*/

#pragma once

#include <QObject>
#include <QDesktopServices>
#include <QUrl>
#include <QCoreApplication>
#include <QDir>

class FolderOpener : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE void openFolder(const QString& path) const;
};
