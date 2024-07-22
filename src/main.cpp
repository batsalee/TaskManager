// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "app_environment.h"
#include "import_qml_components_plugins.h"
#include "import_qml_plugins.h"

// 내가 추가한 헤더들
#include <iostream>
#include <fstream>
#include "FileReader.h"
#include "JsonManager.h"
#include "Schedule.h"

#include <QQmlContext>
//

int main(int argc, char *argv[])
{
    set_qt_environment();

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;



    // 내 코드 시작


    // 1) 파일 열기
    // 나중에 Date가 여기로 값 주도록 변경
    FileReader fr("./Schedule/test.json"); // FileReader 객체 생성
    std::string&& file_content = fr.readFile(); // ★ 여기서 예외처리 나중에 파일 없으면 만드는 기능 추가하기

    // 2) 파일 내용 json으로 파싱
    Document document;
    try {
        if (document.Parse(file_content.c_str()).HasParseError())
            throw std::runtime_error("손상된 일정 파일입니다.");
    }
    catch(const std::runtime_error& re) {
        std::cerr << re.what() << '\n';
        std::cerr << GetParseError_En(document.GetParseError()) << " (" << document.GetErrorOffset() << ")\n";
    }

    // 3) 해석된 json 내용 이중 QList에 넣기
    Schedule scheduler; // 이중리스트 관리자
    scheduler.MakeScheduleList(document);
    engine.rootContext()->setContextProperty("scheduler", &scheduler); // qml이랑 integration




    // 내 코드 끝


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
