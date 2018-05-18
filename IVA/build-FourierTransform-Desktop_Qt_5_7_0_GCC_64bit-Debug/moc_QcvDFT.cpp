/****************************************************************************
** Meta object code from reading C++ file 'QcvDFT.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../FourierTransform/QcvDFT.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QcvDFT.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QcvDFT_t {
    QByteArrayData data[20];
    char stringdata0[255];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QcvDFT_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QcvDFT_t qt_meta_stringdata_QcvDFT = {
    {
QT_MOC_LITERAL(0, 0, 6), // "QcvDFT"
QT_MOC_LITERAL(1, 7, 18), // "squareImageChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 4), // "Mat*"
QT_MOC_LITERAL(4, 32, 5), // "image"
QT_MOC_LITERAL(5, 38, 20), // "spectrumImageChanged"
QT_MOC_LITERAL(6, 59, 19), // "inverseImageChanged"
QT_MOC_LITERAL(7, 79, 6), // "update"
QT_MOC_LITERAL(8, 86, 14), // "setSourceImage"
QT_MOC_LITERAL(9, 101, 13), // "setFilterType"
QT_MOC_LITERAL(10, 115, 10), // "FilterType"
QT_MOC_LITERAL(11, 126, 10), // "filterType"
QT_MOC_LITERAL(12, 137, 12), // "setFiltering"
QT_MOC_LITERAL(13, 150, 9), // "filtering"
QT_MOC_LITERAL(14, 160, 17), // "setLogScaleFactor"
QT_MOC_LITERAL(15, 178, 14), // "logScaleFactor"
QT_MOC_LITERAL(16, 193, 20), // "setLowPassFilterSize"
QT_MOC_LITERAL(17, 214, 7), // "channel"
QT_MOC_LITERAL(18, 222, 10), // "filterSize"
QT_MOC_LITERAL(19, 233, 21) // "setHighPassFilterSize"

    },
    "QcvDFT\0squareImageChanged\0\0Mat*\0image\0"
    "spectrumImageChanged\0inverseImageChanged\0"
    "update\0setSourceImage\0setFilterType\0"
    "FilterType\0filterType\0setFiltering\0"
    "filtering\0setLogScaleFactor\0logScaleFactor\0"
    "setLowPassFilterSize\0channel\0filterSize\0"
    "setHighPassFilterSize"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QcvDFT[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       5,    1,   67,    2, 0x06 /* Public */,
       6,    1,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   73,    2, 0x0a /* Public */,
       8,    1,   74,    2, 0x0a /* Public */,
       9,    1,   77,    2, 0x0a /* Public */,
      12,    1,   80,    2, 0x0a /* Public */,
      14,    1,   83,    2, 0x0a /* Public */,
      16,    2,   86,    2, 0x0a /* Public */,
      19,    2,   91,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, QMetaType::Double,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   17,   18,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   17,   18,

       0        // eod
};

void QcvDFT::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QcvDFT *_t = static_cast<QcvDFT *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->squareImageChanged((*reinterpret_cast< Mat*(*)>(_a[1]))); break;
        case 1: _t->spectrumImageChanged((*reinterpret_cast< Mat*(*)>(_a[1]))); break;
        case 2: _t->inverseImageChanged((*reinterpret_cast< Mat*(*)>(_a[1]))); break;
        case 3: _t->update(); break;
        case 4: _t->setSourceImage((*reinterpret_cast< Mat*(*)>(_a[1]))); break;
        case 5: _t->setFilterType((*reinterpret_cast< FilterType(*)>(_a[1]))); break;
        case 6: _t->setFiltering((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->setLogScaleFactor((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->setLowPassFilterSize((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 9: _t->setHighPassFilterSize((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QcvDFT::*_t)(Mat * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvDFT::squareImageChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QcvDFT::*_t)(Mat * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvDFT::spectrumImageChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QcvDFT::*_t)(Mat * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvDFT::inverseImageChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject QcvDFT::staticMetaObject = {
    { &QcvProcessor::staticMetaObject, qt_meta_stringdata_QcvDFT.data,
      qt_meta_data_QcvDFT,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QcvDFT::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QcvDFT::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QcvDFT.stringdata0))
        return static_cast<void*>(const_cast< QcvDFT*>(this));
    if (!strcmp(_clname, "CvDFT"))
        return static_cast< CvDFT*>(const_cast< QcvDFT*>(this));
    return QcvProcessor::qt_metacast(_clname);
}

int QcvDFT::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void QcvDFT::squareImageChanged(Mat * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QcvDFT::spectrumImageChanged(Mat * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QcvDFT::inverseImageChanged(Mat * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
