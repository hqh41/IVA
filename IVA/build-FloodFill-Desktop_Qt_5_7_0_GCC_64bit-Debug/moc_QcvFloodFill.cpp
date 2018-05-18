/****************************************************************************
** Meta object code from reading C++ file 'QcvFloodFill.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../FloodFill/QcvFloodFill.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QcvFloodFill.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QcvFloodFill_t {
    QByteArrayData data[27];
    char stringdata0[298];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QcvFloodFill_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QcvFloodFill_t qt_meta_stringdata_QcvFloodFill = {
    {
QT_MOC_LITERAL(0, 0, 12), // "QcvFloodFill"
QT_MOC_LITERAL(1, 13, 6), // "update"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 14), // "setDisplayMode"
QT_MOC_LITERAL(4, 36, 12), // "ImageDisplay"
QT_MOC_LITERAL(5, 49, 5), // "index"
QT_MOC_LITERAL(6, 55, 12), // "setFfillMode"
QT_MOC_LITERAL(7, 68, 13), // "FloodFillMode"
QT_MOC_LITERAL(8, 82, 9), // "ffillMode"
QT_MOC_LITERAL(9, 92, 9), // "setLoDiff"
QT_MOC_LITERAL(10, 102, 6), // "loDiff"
QT_MOC_LITERAL(11, 109, 9), // "setUpDiff"
QT_MOC_LITERAL(12, 119, 6), // "upDiff"
QT_MOC_LITERAL(13, 126, 15), // "setConnectivity"
QT_MOC_LITERAL(14, 142, 12), // "connectivity"
QT_MOC_LITERAL(15, 155, 14), // "setInitialSeed"
QT_MOC_LITERAL(16, 170, 5), // "Point"
QT_MOC_LITERAL(17, 176, 11), // "initialSeed"
QT_MOC_LITERAL(18, 188, 11), // "setShowSeed"
QT_MOC_LITERAL(19, 200, 8), // "showSeed"
QT_MOC_LITERAL(20, 209, 18), // "setShowBoundingBox"
QT_MOC_LITERAL(21, 228, 15), // "showBoundingBox"
QT_MOC_LITERAL(22, 244, 15), // "clearFloodPoint"
QT_MOC_LITERAL(23, 260, 1), // "p"
QT_MOC_LITERAL(24, 262, 15), // "Qt::MouseButton"
QT_MOC_LITERAL(25, 278, 6), // "button"
QT_MOC_LITERAL(26, 285, 12) // "setSeedPoint"

    },
    "QcvFloodFill\0update\0\0setDisplayMode\0"
    "ImageDisplay\0index\0setFfillMode\0"
    "FloodFillMode\0ffillMode\0setLoDiff\0"
    "loDiff\0setUpDiff\0upDiff\0setConnectivity\0"
    "connectivity\0setInitialSeed\0Point\0"
    "initialSeed\0setShowSeed\0showSeed\0"
    "setShowBoundingBox\0showBoundingBox\0"
    "clearFloodPoint\0p\0Qt::MouseButton\0"
    "button\0setSeedPoint"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QcvFloodFill[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    1,   70,    2, 0x0a /* Public */,
       6,    1,   73,    2, 0x0a /* Public */,
       9,    1,   76,    2, 0x0a /* Public */,
      11,    1,   79,    2, 0x0a /* Public */,
      13,    1,   82,    2, 0x0a /* Public */,
      15,    1,   85,    2, 0x0a /* Public */,
      18,    1,   88,    2, 0x0a /* Public */,
      20,    1,   91,    2, 0x0a /* Public */,
      22,    2,   94,    2, 0x0a /* Public */,
      26,    2,   99,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::Bool,   21,
    QMetaType::Void, QMetaType::QPoint, 0x80000000 | 24,   23,   25,
    QMetaType::Void, QMetaType::QPoint, 0x80000000 | 24,   23,   25,

       0        // eod
};

void QcvFloodFill::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QcvFloodFill *_t = static_cast<QcvFloodFill *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->update(); break;
        case 1: _t->setDisplayMode((*reinterpret_cast< const ImageDisplay(*)>(_a[1]))); break;
        case 2: _t->setFfillMode((*reinterpret_cast< const FloodFillMode(*)>(_a[1]))); break;
        case 3: _t->setLoDiff((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: _t->setUpDiff((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 5: _t->setConnectivity((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 6: _t->setInitialSeed((*reinterpret_cast< const Point(*)>(_a[1]))); break;
        case 7: _t->setShowSeed((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 8: _t->setShowBoundingBox((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 9: _t->clearFloodPoint((*reinterpret_cast< const QPoint(*)>(_a[1])),(*reinterpret_cast< const Qt::MouseButton(*)>(_a[2]))); break;
        case 10: _t->setSeedPoint((*reinterpret_cast< const QPoint(*)>(_a[1])),(*reinterpret_cast< const Qt::MouseButton(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject QcvFloodFill::staticMetaObject = {
    { &QcvProcessor::staticMetaObject, qt_meta_stringdata_QcvFloodFill.data,
      qt_meta_data_QcvFloodFill,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QcvFloodFill::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QcvFloodFill::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QcvFloodFill.stringdata0))
        return static_cast<void*>(const_cast< QcvFloodFill*>(this));
    if (!strcmp(_clname, "CvFloodFill"))
        return static_cast< CvFloodFill*>(const_cast< QcvFloodFill*>(this));
    return QcvProcessor::qt_metacast(_clname);
}

int QcvFloodFill::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QcvProcessor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
