#pragma once

#include <QObject>
#include <QDesktopServices>
#include <QUrl>

class FolderOpener : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE void openFolder(const QString& path);
};
