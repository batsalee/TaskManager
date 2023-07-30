#include "FolderOpener.h"

void FolderOpener::openFolder(const QString& path)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::toNativeSeparators(QCoreApplication::applicationDirPath() + path)));
    // 설치경로에 한글이 있을것도 감안해서 toNativeSeparators로 인코딩
}
