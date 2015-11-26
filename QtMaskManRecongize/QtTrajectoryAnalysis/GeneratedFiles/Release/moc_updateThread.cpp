/****************************************************************************
** Meta object code from reading C++ file 'updateThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../updateThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'updateThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_updateThread_t {
    QByteArrayData data[8];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_updateThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_updateThread_t qt_meta_stringdata_updateThread = {
    {
QT_MOC_LITERAL(0, 0, 12), // "updateThread"
QT_MOC_LITERAL(1, 13, 13), // "sendSliderVal"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 7), // "sendImg"
QT_MOC_LITERAL(4, 36, 8), // "cv::Mat*"
QT_MOC_LITERAL(5, 45, 8), // "sendInfo"
QT_MOC_LITERAL(6, 54, 11), // "std::string"
QT_MOC_LITERAL(7, 66, 12) // "getThreadEnd"

    },
    "updateThread\0sendSliderVal\0\0sendImg\0"
    "cv::Mat*\0sendInfo\0std::string\0"
    "getThreadEnd"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_updateThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       3,    1,   37,    2, 0x06 /* Public */,
       5,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 6,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void updateThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        updateThread *_t = static_cast<updateThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendSliderVal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sendImg((*reinterpret_cast< cv::Mat*(*)>(_a[1]))); break;
        case 2: _t->sendInfo((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 3: _t->getThreadEnd(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (updateThread::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&updateThread::sendSliderVal)) {
                *result = 0;
            }
        }
        {
            typedef void (updateThread::*_t)(cv::Mat * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&updateThread::sendImg)) {
                *result = 1;
            }
        }
        {
            typedef void (updateThread::*_t)(std::string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&updateThread::sendInfo)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject updateThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_updateThread.data,
      qt_meta_data_updateThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *updateThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *updateThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_updateThread.stringdata0))
        return static_cast<void*>(const_cast< updateThread*>(this));
    return QThread::qt_metacast(_clname);
}

int updateThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void updateThread::sendSliderVal(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void updateThread::sendImg(cv::Mat * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void updateThread::sendInfo(std::string _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
