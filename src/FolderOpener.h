/* FolderOpener
역할
1) 버튼을 누르면 윈도우 내의 특정 폴더를 열어줌
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
