/****************************************************************************
** Meta object code from reading C++ file 'QcvVideoCapture.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../FourierTransform/capture/QcvVideoCapture.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QcvVideoCapture.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QcvVideoCapture_t {
    QByteArrayData data[25];
    char stringdata0[220];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QcvVideoCapture_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QcvVideoCapture_t qt_meta_stringdata_QcvVideoCapture = {
    {
QT_MOC_LITERAL(0, 0, 15), // "QcvVideoCapture"
QT_MOC_LITERAL(1, 16, 7), // "updated"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "finished"
QT_MOC_LITERAL(4, 34, 14), // "messageChanged"
QT_MOC_LITERAL(5, 49, 7), // "message"
QT_MOC_LITERAL(6, 57, 7), // "timeout"
QT_MOC_LITERAL(7, 65, 12), // "imageChanged"
QT_MOC_LITERAL(8, 78, 4), // "Mat*"
QT_MOC_LITERAL(9, 83, 5), // "image"
QT_MOC_LITERAL(10, 89, 12), // "timerChanged"
QT_MOC_LITERAL(11, 102, 5), // "delay"
QT_MOC_LITERAL(12, 108, 9), // "restarted"
QT_MOC_LITERAL(13, 118, 4), // "open"
QT_MOC_LITERAL(14, 123, 8), // "deviceId"
QT_MOC_LITERAL(15, 132, 5), // "width"
QT_MOC_LITERAL(16, 138, 6), // "height"
QT_MOC_LITERAL(17, 145, 8), // "fileName"
QT_MOC_LITERAL(18, 154, 12), // "setFlipVideo"
QT_MOC_LITERAL(19, 167, 9), // "flipVideo"
QT_MOC_LITERAL(20, 177, 7), // "setGray"
QT_MOC_LITERAL(21, 185, 14), // "grayConversion"
QT_MOC_LITERAL(22, 200, 7), // "setSize"
QT_MOC_LITERAL(23, 208, 4), // "size"
QT_MOC_LITERAL(24, 213, 6) // "update"

    },
    "QcvVideoCapture\0updated\0\0finished\0"
    "messageChanged\0message\0timeout\0"
    "imageChanged\0Mat*\0image\0timerChanged\0"
    "delay\0restarted\0open\0deviceId\0width\0"
    "height\0fileName\0setFlipVideo\0flipVideo\0"
    "setGray\0grayConversion\0setSize\0size\0"
    "update"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QcvVideoCapture[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06 /* Public */,
       3,    0,  100,    2, 0x06 /* Public */,
       4,    2,  101,    2, 0x06 /* Public */,
       4,    1,  106,    2, 0x26 /* Public | MethodCloned */,
       7,    1,  109,    2, 0x06 /* Public */,
      10,    1,  112,    2, 0x06 /* Public */,
      12,    0,  115,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    3,  116,    2, 0x0a /* Public */,
      13,    2,  123,    2, 0x2a /* Public | MethodCloned */,
      13,    1,  128,    2, 0x2a /* Public | MethodCloned */,
      13,    3,  131,    2, 0x0a /* Public */,
      13,    2,  138,    2, 0x2a /* Public | MethodCloned */,
      13,    1,  143,    2, 0x2a /* Public | MethodCloned */,
      18,    1,  146,    2, 0x0a /* Public */,
      20,    1,  149,    2, 0x0a /* Public */,
      22,    1,  152,    2, 0x0a /* Public */,
      24,    0,  155,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    5,    6,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Bool, QMetaType::Int, QMetaType::UInt, QMetaType::UInt,   14,   15,   16,
    QMetaType::Bool, QMetaType::Int, QMetaType::UInt,   14,   15,
    QMetaType::Bool, QMetaType::Int,   14,
    QMetaType::Bool, QMetaType::QString, QMetaType::UInt, QMetaType::UInt,   17,   15,   16,
    QMetaType::Bool, QMetaType::QString, QMetaType::UInt,   17,   15,
    QMetaType::Bool, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::Bool,   21,
    QMetaType::Void, QMetaType::QSize,   23,
    QMetaType::Void,

       0        // eod
};

void QcvVideoCapture::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QcvVideoCapture *_t = static_cast<QcvVideoCapture *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updated(); break;
        case 1: _t->finished(); break;
        case 2: _t->messageChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->messageChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->imageChanged((*reinterpret_cast< Mat*(*)>(_a[1]))); break;
        case 5: _t->timerChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 6: _t->restarted(); break;
        case 7: { bool _r = _t->open((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const uint(*)>(_a[2])),(*reinterpret_cast< const uint(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { bool _r = _t->open((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const uint(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->open((*reinterpret_cast< const int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { bool _r = _t->open((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const uint(*)>(_a[2])),(*reinterpret_cast< const uint(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { bool _r = _t->open((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const uint(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: { bool _r = _t->open((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: _t->setFlipVideo((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 14: _t->setGray((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 15: _t->setSize((*reinterpret_cast< const QSize(*)>(_a[1]))); break;
        case 16: _t->update(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QcvVideoCapture::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvVideoCapture::updated)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QcvVideoCapture::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvVideoCapture::finished)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QcvVideoCapture::*_t)(const QString & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvVideoCapture::messageChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QcvVideoCapture::*_t)(Mat * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvVideoCapture::imageChanged)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (QcvVideoCapture::*_t)(const int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvVideoCapture::timerChanged)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (QcvVideoCapture::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvVideoCapture::restarted)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject QcvVideoCapture::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QcvVideoCapture.data,
      qt_meta_data_QcvVideoCapture,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QcvVideoCapture::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QcvVideoCapture::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QcvVideoCapture.stringdata0))
        return static_cast<void*>(const_cast< QcvVideoCapture*>(this));
    return QObject::qt_metacast(_clname);
}

int QcvVideoCapture::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void QcvVideoCapture::updated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void QcvVideoCapture::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void QcvVideoCapture::messageChanged(const QString & _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 4
void QcvVideoCapture::imageChanged(Mat * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QcvVideoCapture::timerChanged(const int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QcvVideoCapture::restarted()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
