/****************************************************************************
** Meta object code from reading C++ file 'QcvMatWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Filter_and_Derivatives/matWidgets/QcvMatWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QcvMatWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QcvMatWidget_t {
    QByteArrayData data[15];
    char stringdata0[145];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QcvMatWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QcvMatWidget_t qt_meta_stringdata_QcvMatWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "QcvMatWidget"
QT_MOC_LITERAL(1, 13, 10), // "pressPoint"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 1), // "p"
QT_MOC_LITERAL(4, 27, 15), // "Qt::MouseButton"
QT_MOC_LITERAL(5, 43, 6), // "button"
QT_MOC_LITERAL(6, 50, 9), // "dragPoint"
QT_MOC_LITERAL(7, 60, 12), // "releasePoint"
QT_MOC_LITERAL(8, 73, 16), // "releaseSelection"
QT_MOC_LITERAL(9, 90, 1), // "r"
QT_MOC_LITERAL(10, 92, 14), // "setSourceImage"
QT_MOC_LITERAL(11, 107, 4), // "Mat*"
QT_MOC_LITERAL(12, 112, 11), // "sourceImage"
QT_MOC_LITERAL(13, 124, 6), // "update"
QT_MOC_LITERAL(14, 131, 13) // "screenChanged"

    },
    "QcvMatWidget\0pressPoint\0\0p\0Qt::MouseButton\0"
    "button\0dragPoint\0releasePoint\0"
    "releaseSelection\0r\0setSourceImage\0"
    "Mat*\0sourceImage\0update\0screenChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QcvMatWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,
       6,    1,   54,    2, 0x06 /* Public */,
       7,    2,   57,    2, 0x06 /* Public */,
       8,    2,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   67,    2, 0x0a /* Public */,
      13,    0,   70,    2, 0x0a /* Public */,
      14,    0,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPoint, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QPoint,    3,
    QMetaType::Void, QMetaType::QPoint, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QRect, 0x80000000 | 4,    9,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QcvMatWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QcvMatWidget *_t = static_cast<QcvMatWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pressPoint((*reinterpret_cast< const QPoint(*)>(_a[1])),(*reinterpret_cast< const Qt::MouseButton(*)>(_a[2]))); break;
        case 1: _t->dragPoint((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 2: _t->releasePoint((*reinterpret_cast< const QPoint(*)>(_a[1])),(*reinterpret_cast< const Qt::MouseButton(*)>(_a[2]))); break;
        case 3: _t->releaseSelection((*reinterpret_cast< const QRect(*)>(_a[1])),(*reinterpret_cast< const Qt::MouseButton(*)>(_a[2]))); break;
        case 4: _t->setSourceImage((*reinterpret_cast< Mat*(*)>(_a[1]))); break;
        case 5: _t->update(); break;
        case 6: _t->screenChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QcvMatWidget::*_t)(const QPoint & , const Qt::MouseButton & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvMatWidget::pressPoint)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QcvMatWidget::*_t)(const QPoint & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvMatWidget::dragPoint)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QcvMatWidget::*_t)(const QPoint & , const Qt::MouseButton & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvMatWidget::releasePoint)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QcvMatWidget::*_t)(const QRect & , const Qt::MouseButton & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvMatWidget::releaseSelection)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject QcvMatWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QcvMatWidget.data,
      qt_meta_data_QcvMatWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QcvMatWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QcvMatWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QcvMatWidget.stringdata0))
        return static_cast<void*>(const_cast< QcvMatWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QcvMatWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void QcvMatWidget::pressPoint(const QPoint & _t1, const Qt::MouseButton & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QcvMatWidget::dragPoint(const QPoint & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QcvMatWidget::releasePoint(const QPoint & _t1, const Qt::MouseButton & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QcvMatWidget::releaseSelection(const QRect & _t1, const Qt::MouseButton & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
