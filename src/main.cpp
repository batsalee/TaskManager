// Qt ���� header
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "app_environment.h"
#include "import_qml_components_plugins.h"
#include "import_qml_plugins.h"

// ���� �߰��� �����
#include <iostream>

#include "FileReader.h"
#include "FileWriter.h"
#include "JsonManager.h"
#include "Schedule.h"

int main(int argc, char *argv[])
{
    set_qt_environment();

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;



    // �� �ڵ� ����


    // 1) ���� ����
    // ���߿� Date�� ����� �� �ֵ��� ����
    FileReader fr("./Schedule/test.json"); // FileReader ��ü ����
    std::string&& file_content = fr.ReadFile(); // �� ���⼭ ����ó�� ���߿� ���� ������ ����� ��� �߰��ϱ�

    // 2) ���� ���� json���� �Ľ�
    Document document;
    try {
        if (document.Parse(file_content.c_str()).HasParseError())
            throw std::runtime_error("�ջ�� ���� �����Դϴ�.");
    }
    catch(const std::runtime_error& re) {
        std::cerr << re.what() << '\n';
        std::cerr << GetParseError_En(document.GetParseError()) << " (" << document.GetErrorOffset() << ")\n";
    }

    // 3) �ؼ��� json ���� ���� QList�� �ֱ�
    Schedule scheduler; // ���߸���Ʈ ������
    scheduler.ConvertJsonToScheduleList(document);

    qRegisterMetaType<Task>("Task"); // Task ����ü QML�� ���
    engine.rootContext()->setContextProperty("scheduler", &scheduler); // qml�̶� integration

/*
    // ��������� ���߸���Ʈ -> json��ȯ �� ���� �׽�Ʈ
    std::string json_for_saving = scheduler.ConvertScheduleListToJson();
    FileWriter fw("./Schedule/test2.json");
    fw.WriteFile(json_for_saving);
*/

    // �� �ڵ� ��


    const QUrl url(u"qrc:/qt/qml/Main/main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");

    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
