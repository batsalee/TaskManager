/* ForderOpener
 *
역할
1) 버튼을 누르면 윈도우 내의 특정 폴더를 열어줌

구현방식
1) qml로부터 상대경로를 받아온 후 .exe파일이 있는 절대경로와 합쳐주고,
   한글이 포함되어 있을 수 있으므로 인코딩해서
   QDesktopServices에 경로를 전달해주면 폴더가 열리는 방식

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
    Q_INVOKABLE void openFolder(const QString& path);
};
