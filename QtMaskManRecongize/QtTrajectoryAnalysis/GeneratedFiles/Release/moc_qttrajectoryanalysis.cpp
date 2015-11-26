/****************************************************************************
** Meta object code from reading C++ file 'qttrajectoryanalysis.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qttrajectoryanalysis.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qttrajectoryanalysis.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QtTrajectoryAnalysis_t {
    QByteArrayData data[18];
    char stringdata0[294];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtTrajectoryAnalysis_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtTrajectoryAnalysis_t qt_meta_stringdata_QtTrajectoryAnalysis = {
    {
QT_MOC_LITERAL(0, 0, 20), // "QtTrajectoryAnalysis"
QT_MOC_LITERAL(1, 21, 19), // "on_pBtn_Run_clicked"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 23), // "on_pBtn_forward_clicked"
QT_MOC_LITERAL(4, 66, 24), // "on_pBtn_backward_clicked"
QT_MOC_LITERAL(5, 91, 28), // "on_pBtn_OutputFolder_clicked"
QT_MOC_LITERAL(6, 120, 20), // "on_pBtn_exit_clicked"
QT_MOC_LITERAL(7, 141, 24), // "on_pBtn_minimize_clicked"
QT_MOC_LITERAL(8, 166, 16), // "updateProcessBar"
QT_MOC_LITERAL(9, 183, 12), // "getThreadEnd"
QT_MOC_LITERAL(10, 196, 13), // "getThreadStop"
QT_MOC_LITERAL(11, 210, 13), // "getThreadFail"
QT_MOC_LITERAL(12, 224, 9), // "updateImg"
QT_MOC_LITERAL(13, 234, 8), // "cv::Mat*"
QT_MOC_LITERAL(14, 243, 15), // "updateEventInfo"
QT_MOC_LITERAL(15, 259, 11), // "std::string"
QT_MOC_LITERAL(16, 271, 12), // "closeWaitDlg"
QT_MOC_LITERAL(17, 284, 9) // "batchDone"

    },
    "QtTrajectoryAnalysis\0on_pBtn_Run_clicked\0"
    "\0on_pBtn_forward_clicked\0"
    "on_pBtn_backward_clicked\0"
    "on_pBtn_OutputFolder_clicked\0"
    "on_pBtn_exit_clicked\0on_pBtn_minimize_clicked\0"
    "updateProcessBar\0getThreadEnd\0"
    "getThreadStop\0getThreadFail\0updateImg\0"
    "cv::Mat*\0updateEventInfo\0std::string\0"
    "closeWaitDlg\0batchDone"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtTrajectoryAnalysis[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    1,   90,    2, 0x08 /* Private */,
       9,    0,   93,    2, 0x08 /* Private */,
      10,    0,   94,    2, 0x08 /* Private */,
      11,    0,   95,    2, 0x08 /* Private */,
      12,    1,   96,    2, 0x08 /* Private */,
      14,    1,   99,    2, 0x08 /* Private */,
      16,    0,  102,    2, 0x08 /* Private */,
      17,    0,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,    2,
    QMetaType::Void, 0x80000000 | 15,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QtTrajectoryAnalysis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QtTrajectoryAnalysis *_t = static_cast<QtTrajectoryAnalysis *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pBtn_Run_clicked(); break;
        case 1: _t->on_pBtn_forward_clicked(); break;
        case 2: _t->on_pBtn_backward_clicked(); break;
        case 3: _t->on_pBtn_OutputFolder_clicked(); break;
        case 4: _t->on_pBtn_exit_clicked(); break;
        case 5: _t->on_pBtn_minimize_clicked(); break;
        case 6: _t->updateProcessBar((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->getThreadEnd(); break;
        case 8: _t->getThreadStop(); break;
        case 9: _t->getThreadFail(); break;
        case 10: _t->updateImg((*reinterpret_cast< cv::Mat*(*)>(_a[1]))); break;
        case 11: _t->updateEventInfo((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 12: _t->closeWaitDlg(); break;
        case 13: _t->batchDone(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< std::string >(); break;
            }
            break;
        }
    }
}

const QMetaObject QtTrajectoryAnalysis::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QtTrajectoryAnalysis.data,
      qt_meta_data_QtTrajectoryAnalysis,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QtTrajectoryAnalysis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtTrajectoryAnalysis::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QtTrajectoryAnalysis.stringdata0))
        return static_cast<void*>(const_cast< QtTrajectoryAnalysis*>(this));
    return QDialog::qt_metacast(_clname);
}

int QtTrajectoryAnalysis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
