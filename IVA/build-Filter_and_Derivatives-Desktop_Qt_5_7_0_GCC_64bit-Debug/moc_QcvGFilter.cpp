/****************************************************************************
** Meta object code from reading C++ file 'QcvGFilter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Filter_and_Derivatives/QcvGFilter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QcvGFilter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QcvGFilter_t {
    QByteArrayData data[22];
    char stringdata0[247];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QcvGFilter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QcvGFilter_t qt_meta_stringdata_QcvGFilter = {
    {
QT_MOC_LITERAL(0, 0, 10), // "QcvGFilter"
QT_MOC_LITERAL(1, 11, 17), // "kernelSizeChanged"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 10), // "kernelSize"
QT_MOC_LITERAL(4, 41, 6), // "update"
QT_MOC_LITERAL(5, 48, 14), // "setSourceImage"
QT_MOC_LITERAL(6, 63, 4), // "Mat*"
QT_MOC_LITERAL(7, 68, 5), // "image"
QT_MOC_LITERAL(8, 74, 13), // "setKernelSize"
QT_MOC_LITERAL(9, 88, 8), // "setSigma"
QT_MOC_LITERAL(10, 97, 5), // "sigma"
QT_MOC_LITERAL(11, 103, 17), // "setThresholdLevel"
QT_MOC_LITERAL(12, 121, 14), // "thresholdLevel"
QT_MOC_LITERAL(13, 136, 14), // "setHarrisKappa"
QT_MOC_LITERAL(14, 151, 11), // "harrisKappa"
QT_MOC_LITERAL(15, 163, 14), // "setDisplayMode"
QT_MOC_LITERAL(16, 178, 12), // "ImageDisplay"
QT_MOC_LITERAL(17, 191, 11), // "displayMode"
QT_MOC_LITERAL(18, 203, 11), // "setEdgeMode"
QT_MOC_LITERAL(19, 215, 11), // "EdgeDisplay"
QT_MOC_LITERAL(20, 227, 8), // "edgeMode"
QT_MOC_LITERAL(21, 236, 10) // "standalone"

    },
    "QcvGFilter\0kernelSizeChanged\0\0kernelSize\0"
    "update\0setSourceImage\0Mat*\0image\0"
    "setKernelSize\0setSigma\0sigma\0"
    "setThresholdLevel\0thresholdLevel\0"
    "setHarrisKappa\0harrisKappa\0setDisplayMode\0"
    "ImageDisplay\0displayMode\0setEdgeMode\0"
    "EdgeDisplay\0edgeMode\0standalone"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QcvGFilter[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   67,    2, 0x0a /* Public */,
       5,    1,   68,    2, 0x0a /* Public */,
       8,    1,   71,    2, 0x0a /* Public */,
       9,    1,   74,    2, 0x0a /* Public */,
      11,    1,   77,    2, 0x0a /* Public */,
      13,    1,   80,    2, 0x0a /* Public */,
      15,    1,   83,    2, 0x0a /* Public */,
      18,    2,   86,    2, 0x0a /* Public */,
      18,    1,   91,    2, 0x2a /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Double,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Double,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 19, QMetaType::Bool,   20,   21,
    QMetaType::Void, 0x80000000 | 19,   20,

       0        // eod
};

void QcvGFilter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QcvGFilter *_t = static_cast<QcvGFilter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->kernelSizeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->update(); break;
        case 2: _t->setSourceImage((*reinterpret_cast< Mat*(*)>(_a[1]))); break;
        case 3: _t->setKernelSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setSigma((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->setThresholdLevel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setHarrisKappa((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->setDisplayMode((*reinterpret_cast< const ImageDisplay(*)>(_a[1]))); break;
        case 8: _t->setEdgeMode((*reinterpret_cast< const EdgeDisplay(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 9: _t->setEdgeMode((*reinterpret_cast< const EdgeDisplay(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QcvGFilter::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvGFilter::kernelSizeChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject QcvGFilter::staticMetaObject = {
    { &QcvProcessor::staticMetaObject, qt_meta_stringdata_QcvGFilter.data,
      qt_meta_data_QcvGFilter,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QcvGFilter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QcvGFilter::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QcvGFilter.stringdata0))
        return static_cast<void*>(const_cast< QcvGFilter*>(this));
    if (!strcmp(_clname, "CvGFilter"))
        return static_cast< CvGFilter*>(const_cast< QcvGFilter*>(this));
    return QcvProcessor::qt_metacast(_clname);
}

int QcvGFilter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QcvProcessor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void QcvGFilter::kernelSizeChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
