#include "FolderOpener.h"

void FolderOpener::openFolder(const QString& path) const
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::toNativeSeparators(QCoreApplication::applicationDirPath() + path)));
    // ��ġ��ο� �ѱ��� �����͵� �����ؼ� toNativeSeparators�� ���ڵ�
}
