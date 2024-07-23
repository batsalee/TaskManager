#pragma once

#include <QObject>
#include <QString>
#include <QMetaType>

using Task = struct task {
    Q_GADGET
    Q_PROPERTY(QString title MEMBER title)
    Q_PROPERTY(qint32 importance MEMBER importance)

public:
    QString title;
    qint32 importance;
};

Q_DECLARE_METATYPE(Task)
