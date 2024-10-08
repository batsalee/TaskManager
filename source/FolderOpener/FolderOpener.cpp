#include "FolderOpener.h"

/* openFolder()
용도 : 지정된 경로의 폴더를 윈도우 탐색기로 열어줌, 개인이 자주 사용하는 파일들을 실행하기 편하도록 구현
시퀀스 : 사용자가 qml측의 버튼을 누르면 윈도우 탐색기로 해당 경로의 폴더를 열어줌

- 설치경로에 한글이 있을것도 감안해서 toNativeSeparators로 인코딩
*/
void FolderOpener::openFolder(const QString& path) const
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::toNativeSeparators(QCoreApplication::applicationDirPath() + path)));    
}
