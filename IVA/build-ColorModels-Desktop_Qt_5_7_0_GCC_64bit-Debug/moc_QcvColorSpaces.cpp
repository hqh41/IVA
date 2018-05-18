/****************************************************************************
** Meta object code from reading C++ file 'QcvColorSpaces.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ColorModels/QcvColorSpaces.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QcvColorSpaces.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QcvColorSpaces_t {
    QByteArrayData data[13];
    char stringdata0[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QcvColorSpaces_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QcvColorSpaces_t qt_meta_stringdata_QcvColorSpaces = {
    {
QT_MOC_LITERAL(0, 0, 14), // "QcvColorSpaces"
QT_MOC_LITERAL(1, 15, 6), // "update"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 20), // "setDisplayImageIndex"
QT_MOC_LITERAL(4, 44, 7), // "Display"
QT_MOC_LITERAL(5, 52, 5), // "index"
QT_MOC_LITERAL(6, 58, 15), // "setColorChannel"
QT_MOC_LITERAL(7, 74, 9), // "ShowColor"
QT_MOC_LITERAL(8, 84, 1), // "c"
QT_MOC_LITERAL(9, 86, 5), // "value"
QT_MOC_LITERAL(10, 92, 17), // "setHueDisplayMode"
QT_MOC_LITERAL(11, 110, 10), // "HueDisplay"
QT_MOC_LITERAL(12, 121, 4) // "mode"

    },
    "QcvColorSpaces\0update\0\0setDisplayImageIndex\0"
    "Display\0index\0setColorChannel\0ShowColor\0"
    "c\0value\0setHueDisplayMode\0HueDisplay\0"
    "mode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QcvColorSpaces[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    1,   35,    2, 0x0a /* Public */,
       6,    2,   38,    2, 0x0a /* Public */,
      10,    1,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Bool,    8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,

       0        // eod
};

void QcvColorSpaces::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QcvColorSpaces *_t = static_cast<QcvColorSpaces *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->update(); break;
        case 1: _t->setDisplayImageIndex((*reinterpret_cast< const Display(*)>(_a[1]))); break;
        case 2: _t->setColorChannel((*reinterpret_cast< const ShowColor(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 3: _t->setHueDisplayMode((*reinterpret_cast< const HueDisplay(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QcvColorSpaces::staticMetaObject = {
    { &QcvProcessor::staticMetaObject, qt_meta_stringdata_QcvColorSpaces.data,
      qt_meta_data_QcvColorSpaces,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QcvColorSpaces::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QcvColorSpaces::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QcvColorSpaces.stringdata0))
        return static_cast<void*>(const_cast< QcvColorSpaces*>(this));
    if (!strcmp(_clname, "CvColorSpaces"))
        return static_cast< CvColorSpaces*>(const_cast< QcvColorSpaces*>(this));
    return QcvProcessor::qt_metacast(_clname);
}

int QcvColorSpaces::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QcvProcessor::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
