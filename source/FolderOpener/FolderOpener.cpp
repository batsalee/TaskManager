#include "FolderOpener.h"

/* openFolder()
�뵵 : ������ ����� ������ ������ Ž����� ������, Schedule �ܿ� ���� ���ϵ��� �����ϱ� ���ϵ��� ����
������ : ����ڰ� qml���� ��ư�� ������ ������ Ž����� �ش� ����� ������ ������
*/
void FolderOpener::openFolder(const QString& path) const
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::toNativeSeparators(QCoreApplication::applicationDirPath() + path)));
    // ��ġ��ο� �ѱ��� �����͵� �����ؼ� toNativeSeparators�� ���ڵ�
}
