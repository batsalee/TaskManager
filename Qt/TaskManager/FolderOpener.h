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
