/* FolderOpener.h

1. Ŭ���� ����
�ٸ� Ŭ�����ʹ� ������� ���� qml���� ȣ���ϸ� ������ ������ ������

2. �뵵
������ ����� ������ ������ Ž����� ������, ������ ���� ����ϴ� ���ϵ��� �����ϱ� ���ϵ��� ����

3. �������
qml�� ��ư�� ������ ������ ���� Ư�� ������ �����ֵ��� Q_INVOKABLE�� ����
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
