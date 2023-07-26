#include "FolderOpener.h"

void FolderOpener::openFolder(const QString& path)
{
    QDesktopServices::openUrl(QUrl(path));
}
