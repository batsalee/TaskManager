QT += quick

SOURCES += \
        Date.cpp \
        FolderOpener.cpp \
        Scheduler.cpp \
        main.cpp

resources.files = \
                main.qml \
                TaskList.qml \
                ButtonList.qml \
                TitleBar.qml \
                TextInputWindow.qml \
                InformationWindow.qml \
                Resizer.qml

resources.prefix = /$${TARGET}
RESOURCES += resources

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Date.h \
    FolderOpener.h \
    Scheduler.h

DISTFILES += \
    ButtonList.qml \
    InformationWindow.qml \
    Resizer.qml \
    TaskInsertWindow.qml \
    TaskList.qml \
    TaskUpdateWindow.qml \
    TitleBar.qml
