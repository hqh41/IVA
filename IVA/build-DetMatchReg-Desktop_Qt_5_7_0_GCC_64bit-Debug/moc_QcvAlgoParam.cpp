/****************************************************************************
** Meta object code from reading C++ file 'QcvAlgoParam.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../DetMatchReg/algoParams/QcvAlgoParam.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QcvAlgoParam.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QcvAlgoParam_t {
    QByteArrayData data[9];
    char stringdata0[100];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QcvAlgoParam_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QcvAlgoParam_t qt_meta_stringdata_QcvAlgoParam = {
    {
QT_MOC_LITERAL(0, 0, 12), // "QcvAlgoParam"
QT_MOC_LITERAL(1, 13, 12), // "setBoolValue"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 5), // "value"
QT_MOC_LITERAL(4, 33, 11), // "setIntValue"
QT_MOC_LITERAL(5, 45, 13), // "setIndexValue"
QT_MOC_LITERAL(6, 59, 5), // "index"
QT_MOC_LITERAL(7, 65, 14), // "setDoubleValue"
QT_MOC_LITERAL(8, 80, 19) // "resetToDefaultValue"

    },
    "QcvAlgoParam\0setBoolValue\0\0value\0"
    "setIntValue\0setIndexValue\0index\0"
    "setDoubleValue\0resetToDefaultValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QcvAlgoParam[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       4,    1,   42,    2, 0x0a /* Public */,
       5,    1,   45,    2, 0x0a /* Public */,
       7,    1,   48,    2, 0x0a /* Public */,
       8,    0,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Bool,

       0        // eod
};

void QcvAlgoParam::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QcvAlgoParam *_t = static_cast<QcvAlgoParam *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setBoolValue((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 1: _t->setIntValue((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: _t->setIndexValue((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 3: _t->setDoubleValue((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 4: { bool _r = _t->resetToDefaultValue();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject QcvAlgoParam::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QcvAlgoParam.data,
      qt_meta_data_QcvAlgoParam,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QcvAlgoParam::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QcvAlgoParam::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QcvAlgoParam.stringdata0))
        return static_cast<void*>(const_cast< QcvAlgoParam*>(this));
    if (!strcmp(_clname, "CvAlgoParam"))
        return static_cast< CvAlgoParam*>(const_cast< QcvAlgoParam*>(this));
    return QObject::qt_metacast(_clname);
}

int QcvAlgoParam::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
