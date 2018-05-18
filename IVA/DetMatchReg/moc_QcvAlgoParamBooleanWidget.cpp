/****************************************************************************
** Meta object code from reading C++ file 'QcvAlgoParamBooleanWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "crtlWidgets/QcvAlgoParamBooleanWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QcvAlgoParamBooleanWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QcvAlgoParamBooleanWidget_t {
    QByteArrayData data[6];
    char stringdata0[98];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QcvAlgoParamBooleanWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QcvAlgoParamBooleanWidget_t qt_meta_stringdata_QcvAlgoParamBooleanWidget = {
    {
QT_MOC_LITERAL(0, 0, 25), // "QcvAlgoParamBooleanWidget"
QT_MOC_LITERAL(1, 26, 16), // "parameterUpdated"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 5), // "value"
QT_MOC_LITERAL(4, 50, 24), // "on_checkBox_stateChanged"
QT_MOC_LITERAL(5, 75, 22) // "on_resetButton_clicked"

    },
    "QcvAlgoParamBooleanWidget\0parameterUpdated\0"
    "\0value\0on_checkBox_stateChanged\0"
    "on_resetButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QcvAlgoParamBooleanWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       1,    1,   35,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   38,    2, 0x08 /* Private */,
       5,    0,   41,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

       0        // eod
};

void QcvAlgoParamBooleanWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QcvAlgoParamBooleanWidget *_t = static_cast<QcvAlgoParamBooleanWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->parameterUpdated(); break;
        case 1: _t->parameterUpdated((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 2: _t->on_checkBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_resetButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QcvAlgoParamBooleanWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvAlgoParamBooleanWidget::parameterUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QcvAlgoParamBooleanWidget::*_t)(const bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvAlgoParamBooleanWidget::parameterUpdated)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject QcvAlgoParamBooleanWidget::staticMetaObject = {
    { &QcvAlgoParamWidget::staticMetaObject, qt_meta_stringdata_QcvAlgoParamBooleanWidget.data,
      qt_meta_data_QcvAlgoParamBooleanWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QcvAlgoParamBooleanWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QcvAlgoParamBooleanWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QcvAlgoParamBooleanWidget.stringdata0))
        return static_cast<void*>(const_cast< QcvAlgoParamBooleanWidget*>(this));
    return QcvAlgoParamWidget::qt_metacast(_clname);
}

int QcvAlgoParamBooleanWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QcvAlgoParamWidget::qt_metacall(_c, _id, _a);
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
void QcvAlgoParamBooleanWidget::parameterUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void QcvAlgoParamBooleanWidget::parameterUpdated(const bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
