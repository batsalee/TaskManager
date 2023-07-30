/****************************************************************************
** Meta object code from reading C++ file 'Scheduler.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Qt/TaskManager/Scheduler.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Scheduler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSSchedulerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSSchedulerENDCLASS = QtMocHelpers::stringData(
    "Scheduler",
    "removeTask",
    "",
    "getTaskList",
    "QList<QList<QString>>"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSSchedulerENDCLASS_t {
    uint offsetsAndSizes[10];
    char stringdata0[10];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[22];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSSchedulerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSSchedulerENDCLASS_t qt_meta_stringdata_CLASSSchedulerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 9),  // "Scheduler"
        QT_MOC_LITERAL(10, 10),  // "removeTask"
        QT_MOC_LITERAL(21, 0),  // ""
        QT_MOC_LITERAL(22, 11),  // "getTaskList"
        QT_MOC_LITERAL(34, 21)   // "QList<QList<QString>>"
    },
    "Scheduler",
    "removeTask",
    "",
    "getTaskList",
    "QList<QList<QString>>"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSSchedulerENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   26,    2, 0x02,    1 /* Public */,
       3,    0,   31,    2, 0x02,    4 /* Public */,

 // methods: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    0x80000000 | 4,

       0        // eod
};

Q_CONSTINIT const QMetaObject Scheduler::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSSchedulerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSSchedulerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSSchedulerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Scheduler, std::true_type>,
        // method 'removeTask'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint32, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint32, std::false_type>,
        // method 'getTaskList'
        QtPrivate::TypeAndForceComplete<QList<QList<QString>>, std::false_type>
    >,
    nullptr
} };

void Scheduler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Scheduler *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->removeTask((*reinterpret_cast< std::add_pointer_t<qint32>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qint32>>(_a[2]))); break;
        case 1: { QList<QList<QString>> _r = _t->getTaskList();
            if (_a[0]) *reinterpret_cast< QList<QList<QString>>*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject *Scheduler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Scheduler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSSchedulerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Scheduler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
