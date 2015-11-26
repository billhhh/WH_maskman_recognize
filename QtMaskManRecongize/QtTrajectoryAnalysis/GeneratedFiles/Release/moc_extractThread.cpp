/****************************************************************************
** Meta object code from reading C++ file 'extractThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../extractThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'extractThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_extractThread_t {
    QByteArrayData data[6];
    char stringdata0[61];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_extractThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_extractThread_t qt_meta_stringdata_extractThread = {
    {
QT_MOC_LITERAL(0, 0, 13), // "extractThread"
QT_MOC_LITERAL(1, 14, 13), // "sendSliderVal"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 10), // "threadStop"
QT_MOC_LITERAL(4, 40, 9), // "threadEnd"
QT_MOC_LITERAL(5, 50, 10) // "threadFail"

    },
    "extractThread\0sendSliderVal\0\0threadStop\0"
    "threadEnd\0threadFail"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_extractThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       3,    0,   37,    2, 0x06 /* Public */,
       4,    0,   38,    2, 0x06 /* Public */,
       5,    0,   39,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void extractThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        extractThread *_t = static_cast<extractThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendSliderVal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->threadStop(); break;
        case 2: _t->threadEnd(); break;
        case 3: _t->threadFail(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (extractThread::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&extractThread::sendSliderVal)) {
                *result = 0;
            }
        }
        {
            typedef void (extractThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&extractThread::threadStop)) {
                *result = 1;
            }
        }
        {
            typedef void (extractThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&extractThread::threadEnd)) {
                *result = 2;
            }
        }
        {
            typedef void (extractThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&extractThread::threadFail)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject extractThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_extractThread.data,
      qt_meta_data_extractThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *extractThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *extractThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_extractThread.stringdata0))
        return static_cast<void*>(const_cast< extractThread*>(this));
    return QThread::qt_metacast(_clname);
}

int extractThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void extractThread::sendSliderVal(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void extractThread::threadStop()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void extractThread::threadEnd()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void extractThread::threadFail()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
