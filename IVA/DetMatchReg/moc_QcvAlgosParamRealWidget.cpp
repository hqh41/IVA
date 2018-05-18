/****************************************************************************
** Meta object code from reading C++ file 'QcvAlgosParamRealWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "crtlWidgets/QcvAlgosParamRealWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QcvAlgosParamRealWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QcvAlgosParamRealWidget_t {
    QByteArrayData data[9];
    char stringdata0[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QcvAlgosParamRealWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QcvAlgosParamRealWidget_t qt_meta_stringdata_QcvAlgosParamRealWidget = {
    {
QT_MOC_LITERAL(0, 0, 23), // "QcvAlgosParamRealWidget"
QT_MOC_LITERAL(1, 24, 16), // "parameterUpdated"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 5), // "value"
QT_MOC_LITERAL(4, 48, 29), // "on_doubleSpinBox_valueChanged"
QT_MOC_LITERAL(5, 78, 6), // "dvalue"
QT_MOC_LITERAL(6, 85, 32), // "on_horizontalSlider_valueChanged"
QT_MOC_LITERAL(7, 118, 6), // "ivalue"
QT_MOC_LITERAL(8, 125, 22) // "on_resetButton_clicked"

    },
    "QcvAlgosParamRealWidget\0parameterUpdated\0"
    "\0value\0on_doubleSpinBox_valueChanged\0"
    "dvalue\0on_horizontalSlider_valueChanged\0"
    "ivalue\0on_resetButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QcvAlgosParamRealWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       1,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   43,    2, 0x08 /* Private */,
       6,    1,   46,    2, 0x08 /* Private */,
       8,    0,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,

       0        // eod
};

void QcvAlgosParamRealWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QcvAlgosParamRealWidget *_t = static_cast<QcvAlgosParamRealWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->parameterUpdated(); break;
        case 1: _t->parameterUpdated((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 2: _t->on_doubleSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->on_horizontalSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_resetButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QcvAlgosParamRealWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvAlgosParamRealWidget::parameterUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QcvAlgosParamRealWidget::*_t)(const double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvAlgosParamRealWidget::parameterUpdated)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject QcvAlgosParamRealWidget::staticMetaObject = {
    { &QcvAlgoParamWidget::staticMetaObject, qt_meta_stringdata_QcvAlgosParamRealWidget.data,
      qt_meta_data_QcvAlgosParamRealWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QcvAlgosParamRealWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QcvAlgosParamRealWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QcvAlgosParamRealWidget.stringdata0))
        return static_cast<void*>(const_cast< QcvAlgosParamRealWidget*>(this));
    return QcvAlgoParamWidget::qt_metacast(_clname);
}

int QcvAlgosParamRealWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QcvAlgoParamWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void QcvAlgosParamRealWidget::parameterUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void QcvAlgosParamRealWidget::parameterUpdated(const double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
