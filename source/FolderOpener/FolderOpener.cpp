#include "FolderOpener.h"

/* openFolder()
�뵵 : ������ ����� ������ ������ Ž����� ������, ������ ���� ����ϴ� ���ϵ��� �����ϱ� ���ϵ��� ����
������ : ����ڰ� qml���� ��ư�� ������ ������ Ž����� �ش� ����� ������ ������

- ��ġ��ο� �ѱ��� �����͵� �����ؼ� toNativeSeparators�� ���ڵ�
*/
void FolderOpener::openFolder(const QString& path) const
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::toNativeSeparators(QCoreApplication::applicationDirPath() + path)));    
}
