/****************************************************************************
** Meta object code from reading C++ file 'QcvProcessor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "QcvProcessor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QcvProcessor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QcvProcessor_t {
    QByteArrayData data[23];
    char stringdata0[291];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QcvProcessor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QcvProcessor_t qt_meta_stringdata_QcvProcessor = {
    {
QT_MOC_LITERAL(0, 0, 12), // "QcvProcessor"
QT_MOC_LITERAL(1, 13, 7), // "updated"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "finished"
QT_MOC_LITERAL(4, 31, 12), // "imageChanged"
QT_MOC_LITERAL(5, 44, 4), // "Mat*"
QT_MOC_LITERAL(6, 49, 5), // "image"
QT_MOC_LITERAL(7, 55, 18), // "imageColorsChanged"
QT_MOC_LITERAL(8, 74, 16), // "imageSizeChanged"
QT_MOC_LITERAL(9, 91, 18), // "processTimeUpdated"
QT_MOC_LITERAL(10, 110, 14), // "formattedValue"
QT_MOC_LITERAL(11, 125, 24), // "processTimeMinMaxUpdated"
QT_MOC_LITERAL(12, 150, 31), // "const CvProcessor::ProcessTime*"
QT_MOC_LITERAL(13, 182, 4), // "time"
QT_MOC_LITERAL(14, 187, 8), // "sendText"
QT_MOC_LITERAL(15, 196, 7), // "message"
QT_MOC_LITERAL(16, 204, 11), // "sendMessage"
QT_MOC_LITERAL(17, 216, 7), // "timeout"
QT_MOC_LITERAL(18, 224, 6), // "update"
QT_MOC_LITERAL(19, 231, 14), // "setSourceImage"
QT_MOC_LITERAL(20, 246, 17), // "setTimePerFeature"
QT_MOC_LITERAL(21, 264, 5), // "value"
QT_MOC_LITERAL(22, 270, 20) // "resetMeanProcessTime"

    },
    "QcvProcessor\0updated\0\0finished\0"
    "imageChanged\0Mat*\0image\0imageColorsChanged\0"
    "imageSizeChanged\0processTimeUpdated\0"
    "formattedValue\0processTimeMinMaxUpdated\0"
    "const CvProcessor::ProcessTime*\0time\0"
    "sendText\0message\0sendMessage\0timeout\0"
    "update\0setSourceImage\0setTimePerFeature\0"
    "value\0resetMeanProcessTime"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QcvProcessor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,
       3,    0,   95,    2, 0x06 /* Public */,
       4,    0,   96,    2, 0x06 /* Public */,
       4,    1,   97,    2, 0x06 /* Public */,
       7,    0,  100,    2, 0x06 /* Public */,
       8,    0,  101,    2, 0x06 /* Public */,
       9,    1,  102,    2, 0x06 /* Public */,
      11,    1,  105,    2, 0x06 /* Public */,
       9,    1,  108,    2, 0x06 /* Public */,
      14,    1,  111,    2, 0x06 /* Public */,
      16,    2,  114,    2, 0x06 /* Public */,
      16,    1,  119,    2, 0x26 /* Public | MethodCloned */,

 // slots: name, argc, parameters, tag, flags
      18,    0,  122,    2, 0x0a /* Public */,
      19,    1,  123,    2, 0x0a /* Public */,
      20,    1,  126,    2, 0x0a /* Public */,
      22,    0,  129,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   15,   17,
    QMetaType::Void, QMetaType::QString,   15,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::Bool,   21,
    QMetaType::Void,

       0        // eod
};

void QcvProcessor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QcvProcessor *_t = static_cast<QcvProcessor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updated(); break;
        case 1: _t->finished(); break;
        case 2: _t->imageChanged(); break;
        case 3: _t->imageChanged((*reinterpret_cast< Mat*(*)>(_a[1]))); break;
        case 4: _t->imageColorsChanged(); break;
        case 5: _t->imageSizeChanged(); break;
        case 6: _t->processTimeUpdated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->processTimeMinMaxUpdated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->processTimeUpdated((*reinterpret_cast< const CvProcessor::ProcessTime*(*)>(_a[1]))); break;
        case 9: _t->sendText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->sendMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->sendMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->update(); break;
        case 13: _t->setSourceImage((*reinterpret_cast< Mat*(*)>(_a[1]))); break;
        case 14: _t->setTimePerFeature((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 15: _t->resetMeanProcessTime(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QcvProcessor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvProcessor::updated)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QcvProcessor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvProcessor::finished)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QcvProcessor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvProcessor::imageChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QcvProcessor::*_t)(Mat * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvProcessor::imageChanged)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (QcvProcessor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvProcessor::imageColorsChanged)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (QcvProcessor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvProcessor::imageSizeChanged)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (QcvProcessor::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvProcessor::processTimeUpdated)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (QcvProcessor::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvProcessor::processTimeMinMaxUpdated)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (QcvProcessor::*_t)(const CvProcessor::ProcessTime * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvProcessor::processTimeUpdated)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (QcvProcessor::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvProcessor::sendText)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (QcvProcessor::*_t)(const QString & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvProcessor::sendMessage)) {
                *result = 10;
                return;
            }
        }
    }
}

const QMetaObject QcvProcessor::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QcvProcessor.data,
      qt_meta_data_QcvProcessor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QcvProcessor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QcvProcessor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QcvProcessor.stringdata0))
        return static_cast<void*>(const_cast< QcvProcessor*>(this));
    if (!strcmp(_clname, "CvProcessor"))
        return static_cast< CvProcessor*>(const_cast< QcvProcessor*>(this));
    return QObject::qt_metacast(_clname);
}

int QcvProcessor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void QcvProcessor::updated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void QcvProcessor::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void QcvProcessor::imageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void QcvProcessor::imageChanged(Mat * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QcvProcessor::imageColorsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void QcvProcessor::imageSizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void QcvProcessor::processTimeUpdated(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QcvProcessor::processTimeMinMaxUpdated(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void QcvProcessor::processTimeUpdated(const CvProcessor::ProcessTime * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void QcvProcessor::sendText(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void QcvProcessor::sendMessage(const QString & _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_END_MOC_NAMESPACE
