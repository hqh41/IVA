/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../DetMatchReg/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[83];
    char stringdata0[1826];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 11), // "sendMessage"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 7), // "message"
QT_MOC_LITERAL(4, 32, 7), // "timeout"
QT_MOC_LITERAL(5, 40, 11), // "sizeChanged"
QT_MOC_LITERAL(6, 52, 4), // "size"
QT_MOC_LITERAL(7, 57, 13), // "deviceChanged"
QT_MOC_LITERAL(8, 71, 8), // "deviceId"
QT_MOC_LITERAL(9, 80, 5), // "width"
QT_MOC_LITERAL(10, 86, 6), // "height"
QT_MOC_LITERAL(11, 93, 11), // "fileChanged"
QT_MOC_LITERAL(12, 105, 8), // "fileName"
QT_MOC_LITERAL(13, 114, 11), // "flipChanged"
QT_MOC_LITERAL(14, 126, 4), // "flip"
QT_MOC_LITERAL(15, 131, 11), // "grayChanged"
QT_MOC_LITERAL(16, 143, 4), // "gray"
QT_MOC_LITERAL(17, 148, 26), // "timePerFeatureStateChanged"
QT_MOC_LITERAL(18, 175, 5), // "state"
QT_MOC_LITERAL(19, 181, 21), // "detectingStateChanged"
QT_MOC_LITERAL(20, 203, 18), // "featureTypeChanged"
QT_MOC_LITERAL(21, 222, 23), // "CvDetector::FeatureType"
QT_MOC_LITERAL(22, 246, 4), // "type"
QT_MOC_LITERAL(23, 251, 21), // "descriptorTypeChanged"
QT_MOC_LITERAL(24, 273, 35), // "CvDetector::DescriptorExtract..."
QT_MOC_LITERAL(25, 309, 12), // "checkMatcher"
QT_MOC_LITERAL(26, 322, 20), // "matchingStateChanged"
QT_MOC_LITERAL(27, 343, 18), // "matcherTypeChanged"
QT_MOC_LITERAL(28, 362, 22), // "CvMatcher::MatcherType"
QT_MOC_LITERAL(29, 385, 16), // "checkDescriptors"
QT_MOC_LITERAL(30, 402, 18), // "matcherModeChanged"
QT_MOC_LITERAL(31, 421, 20), // "CvMatcher::MatchType"
QT_MOC_LITERAL(32, 442, 4), // "mode"
QT_MOC_LITERAL(33, 447, 10), // "knnChanged"
QT_MOC_LITERAL(34, 458, 5), // "value"
QT_MOC_LITERAL(35, 464, 22), // "radiusThresholdChanged"
QT_MOC_LITERAL(36, 487, 23), // "registeringStateChanged"
QT_MOC_LITERAL(37, 511, 25), // "poseComputingStateChanged"
QT_MOC_LITERAL(38, 537, 16), // "printSizeChanged"
QT_MOC_LITERAL(39, 554, 22), // "reprojThresholdChanged"
QT_MOC_LITERAL(40, 577, 21), // "showModelFrameChanged"
QT_MOC_LITERAL(41, 599, 19), // "showModelBoxChanged"
QT_MOC_LITERAL(42, 619, 27), // "usePreviousPoseStateChanged"
QT_MOC_LITERAL(43, 647, 23), // "cameraParametersChanged"
QT_MOC_LITERAL(44, 671, 8), // "filename"
QT_MOC_LITERAL(45, 680, 20), // "setupProcessorfromUI"
QT_MOC_LITERAL(46, 701, 27), // "on_actionCamera_0_triggered"
QT_MOC_LITERAL(47, 729, 27), // "on_actionCamera_1_triggered"
QT_MOC_LITERAL(48, 757, 23), // "on_actionFile_triggered"
QT_MOC_LITERAL(49, 781, 24), // "on_actionModel_triggered"
QT_MOC_LITERAL(50, 806, 28), // "on_actionCalibData_triggered"
QT_MOC_LITERAL(51, 835, 23), // "on_actionQuit_triggered"
QT_MOC_LITERAL(52, 859, 23), // "on_actionFlip_triggered"
QT_MOC_LITERAL(53, 883, 23), // "on_actionGray_triggered"
QT_MOC_LITERAL(54, 907, 31), // "on_actionOriginalSize_triggered"
QT_MOC_LITERAL(55, 939, 34), // "on_actionConstrainedSize_trig..."
QT_MOC_LITERAL(56, 974, 30), // "on_actionRenderImage_triggered"
QT_MOC_LITERAL(57, 1005, 31), // "on_actionRenderPixmap_triggered"
QT_MOC_LITERAL(58, 1037, 31), // "on_actionRenderOpenGL_triggered"
QT_MOC_LITERAL(59, 1069, 30), // "on_radioButtonOrigSize_clicked"
QT_MOC_LITERAL(60, 1100, 32), // "on_radioButtonCustomSize_clicked"
QT_MOC_LITERAL(61, 1133, 28), // "on_spinBoxWidth_valueChanged"
QT_MOC_LITERAL(62, 1162, 29), // "on_spinBoxHeight_valueChanged"
QT_MOC_LITERAL(63, 1192, 23), // "on_checkBoxFlip_clicked"
QT_MOC_LITERAL(64, 1216, 23), // "on_checkBoxGray_clicked"
QT_MOC_LITERAL(65, 1240, 27), // "on_groupBoxDetector_clicked"
QT_MOC_LITERAL(66, 1268, 7), // "checked"
QT_MOC_LITERAL(67, 1276, 26), // "on_groupBoxMatcher_clicked"
QT_MOC_LITERAL(68, 1303, 28), // "on_groupBoxRegistrar_clicked"
QT_MOC_LITERAL(69, 1332, 39), // "on_comboBoxFeatures_currentIn..."
QT_MOC_LITERAL(70, 1372, 5), // "index"
QT_MOC_LITERAL(71, 1378, 42), // "on_comboBoxDescriptors_curren..."
QT_MOC_LITERAL(72, 1421, 39), // "on_comboBoxShowKPts_currentIn..."
QT_MOC_LITERAL(73, 1461, 42), // "on_comboBoxMatcherType_curren..."
QT_MOC_LITERAL(74, 1504, 42), // "on_comboBoxMatcherMode_curren..."
QT_MOC_LITERAL(75, 1547, 26), // "on_spinBoxKnn_valueChanged"
QT_MOC_LITERAL(76, 1574, 35), // "on_doubleSpinBoxRadius_valueC..."
QT_MOC_LITERAL(77, 1610, 38), // "on_doubleSpinBoxPrintSize_val..."
QT_MOC_LITERAL(78, 1649, 40), // "on_doubleSpinBoxReprojThres_v..."
QT_MOC_LITERAL(79, 1690, 28), // "on_checkBoxShowFrame_clicked"
QT_MOC_LITERAL(80, 1719, 31), // "on_checkBoxShowModelBox_clicked"
QT_MOC_LITERAL(81, 1751, 34), // "on_checkBoxUsePreviousPose_cl..."
QT_MOC_LITERAL(82, 1786, 39) // "on_comboBoxTimeUnit_currentIn..."

    },
    "MainWindow\0sendMessage\0\0message\0timeout\0"
    "sizeChanged\0size\0deviceChanged\0deviceId\0"
    "width\0height\0fileChanged\0fileName\0"
    "flipChanged\0flip\0grayChanged\0gray\0"
    "timePerFeatureStateChanged\0state\0"
    "detectingStateChanged\0featureTypeChanged\0"
    "CvDetector::FeatureType\0type\0"
    "descriptorTypeChanged\0"
    "CvDetector::DescriptorExtractorType\0"
    "checkMatcher\0matchingStateChanged\0"
    "matcherTypeChanged\0CvMatcher::MatcherType\0"
    "checkDescriptors\0matcherModeChanged\0"
    "CvMatcher::MatchType\0mode\0knnChanged\0"
    "value\0radiusThresholdChanged\0"
    "registeringStateChanged\0"
    "poseComputingStateChanged\0printSizeChanged\0"
    "reprojThresholdChanged\0showModelFrameChanged\0"
    "showModelBoxChanged\0usePreviousPoseStateChanged\0"
    "cameraParametersChanged\0filename\0"
    "setupProcessorfromUI\0on_actionCamera_0_triggered\0"
    "on_actionCamera_1_triggered\0"
    "on_actionFile_triggered\0"
    "on_actionModel_triggered\0"
    "on_actionCalibData_triggered\0"
    "on_actionQuit_triggered\0on_actionFlip_triggered\0"
    "on_actionGray_triggered\0"
    "on_actionOriginalSize_triggered\0"
    "on_actionConstrainedSize_triggered\0"
    "on_actionRenderImage_triggered\0"
    "on_actionRenderPixmap_triggered\0"
    "on_actionRenderOpenGL_triggered\0"
    "on_radioButtonOrigSize_clicked\0"
    "on_radioButtonCustomSize_clicked\0"
    "on_spinBoxWidth_valueChanged\0"
    "on_spinBoxHeight_valueChanged\0"
    "on_checkBoxFlip_clicked\0on_checkBoxGray_clicked\0"
    "on_groupBoxDetector_clicked\0checked\0"
    "on_groupBoxMatcher_clicked\0"
    "on_groupBoxRegistrar_clicked\0"
    "on_comboBoxFeatures_currentIndexChanged\0"
    "index\0on_comboBoxDescriptors_currentIndexChanged\0"
    "on_comboBoxShowKPts_currentIndexChanged\0"
    "on_comboBoxMatcherType_currentIndexChanged\0"
    "on_comboBoxMatcherMode_currentIndexChanged\0"
    "on_spinBoxKnn_valueChanged\0"
    "on_doubleSpinBoxRadius_valueChanged\0"
    "on_doubleSpinBoxPrintSize_valueChanged\0"
    "on_doubleSpinBoxReprojThres_valueChanged\0"
    "on_checkBoxShowFrame_clicked\0"
    "on_checkBoxShowModelBox_clicked\0"
    "on_checkBoxUsePreviousPose_clicked\0"
    "on_comboBoxTimeUnit_currentIndexChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      60,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      24,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  314,    2, 0x06 /* Public */,
       1,    1,  319,    2, 0x26 /* Public | MethodCloned */,
       5,    1,  322,    2, 0x06 /* Public */,
       7,    3,  325,    2, 0x06 /* Public */,
      11,    3,  332,    2, 0x06 /* Public */,
      13,    1,  339,    2, 0x06 /* Public */,
      15,    1,  342,    2, 0x06 /* Public */,
      17,    1,  345,    2, 0x06 /* Public */,
      19,    1,  348,    2, 0x06 /* Public */,
      20,    1,  351,    2, 0x06 /* Public */,
      23,    2,  354,    2, 0x06 /* Public */,
      26,    1,  359,    2, 0x06 /* Public */,
      27,    2,  362,    2, 0x06 /* Public */,
      30,    1,  367,    2, 0x06 /* Public */,
      33,    1,  370,    2, 0x06 /* Public */,
      35,    1,  373,    2, 0x06 /* Public */,
      36,    1,  376,    2, 0x06 /* Public */,
      37,    1,  379,    2, 0x06 /* Public */,
      38,    1,  382,    2, 0x06 /* Public */,
      39,    1,  385,    2, 0x06 /* Public */,
      40,    1,  388,    2, 0x06 /* Public */,
      41,    1,  391,    2, 0x06 /* Public */,
      42,    1,  394,    2, 0x06 /* Public */,
      43,    1,  397,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      45,    0,  400,    2, 0x08 /* Private */,
      46,    0,  401,    2, 0x08 /* Private */,
      47,    0,  402,    2, 0x08 /* Private */,
      48,    0,  403,    2, 0x08 /* Private */,
      49,    0,  404,    2, 0x08 /* Private */,
      50,    0,  405,    2, 0x08 /* Private */,
      51,    0,  406,    2, 0x08 /* Private */,
      52,    0,  407,    2, 0x08 /* Private */,
      53,    0,  408,    2, 0x08 /* Private */,
      54,    0,  409,    2, 0x08 /* Private */,
      55,    0,  410,    2, 0x08 /* Private */,
      56,    0,  411,    2, 0x08 /* Private */,
      57,    0,  412,    2, 0x08 /* Private */,
      58,    0,  413,    2, 0x08 /* Private */,
      59,    0,  414,    2, 0x08 /* Private */,
      60,    0,  415,    2, 0x08 /* Private */,
      61,    1,  416,    2, 0x08 /* Private */,
      62,    1,  419,    2, 0x08 /* Private */,
      63,    0,  422,    2, 0x08 /* Private */,
      64,    0,  423,    2, 0x08 /* Private */,
      65,    1,  424,    2, 0x08 /* Private */,
      67,    1,  427,    2, 0x08 /* Private */,
      68,    1,  430,    2, 0x08 /* Private */,
      69,    1,  433,    2, 0x08 /* Private */,
      71,    1,  436,    2, 0x08 /* Private */,
      72,    1,  439,    2, 0x08 /* Private */,
      73,    1,  442,    2, 0x08 /* Private */,
      74,    1,  445,    2, 0x08 /* Private */,
      75,    1,  448,    2, 0x08 /* Private */,
      76,    1,  451,    2, 0x08 /* Private */,
      77,    1,  454,    2, 0x08 /* Private */,
      78,    1,  457,    2, 0x08 /* Private */,
      79,    1,  460,    2, 0x08 /* Private */,
      80,    1,  463,    2, 0x08 /* Private */,
      81,    1,  466,    2, 0x08 /* Private */,
      82,    1,  469,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QSize,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::UInt, QMetaType::UInt,    8,    9,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::UInt, QMetaType::UInt,   12,    9,   10,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void, 0x80000000 | 24, QMetaType::Bool,   22,   25,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, 0x80000000 | 28, QMetaType::Bool,   22,   29,
    QMetaType::Void, 0x80000000 | 31,   32,
    QMetaType::Void, QMetaType::Int,   34,
    QMetaType::Void, QMetaType::Double,   34,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Double,   34,
    QMetaType::Void, QMetaType::Double,   34,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::QString,   44,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   34,
    QMetaType::Void, QMetaType::Int,   34,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   66,
    QMetaType::Void, QMetaType::Bool,   66,
    QMetaType::Void, QMetaType::Bool,   66,
    QMetaType::Void, QMetaType::Int,   70,
    QMetaType::Void, QMetaType::Int,   70,
    QMetaType::Void, QMetaType::Int,   70,
    QMetaType::Void, QMetaType::Int,   70,
    QMetaType::Void, QMetaType::Int,   70,
    QMetaType::Void, QMetaType::Int,   34,
    QMetaType::Void, QMetaType::Double,   34,
    QMetaType::Void, QMetaType::Double,   34,
    QMetaType::Void, QMetaType::Double,   34,
    QMetaType::Void, QMetaType::Bool,   66,
    QMetaType::Void, QMetaType::Bool,   66,
    QMetaType::Void, QMetaType::Bool,   66,
    QMetaType::Void, QMetaType::Int,   70,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->sendMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->sizeChanged((*reinterpret_cast< const QSize(*)>(_a[1]))); break;
        case 3: _t->deviceChanged((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const uint(*)>(_a[2])),(*reinterpret_cast< const uint(*)>(_a[3]))); break;
        case 4: _t->fileChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const uint(*)>(_a[2])),(*reinterpret_cast< const uint(*)>(_a[3]))); break;
        case 5: _t->flipChanged((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 6: _t->grayChanged((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 7: _t->timePerFeatureStateChanged((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 8: _t->detectingStateChanged((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 9: _t->featureTypeChanged((*reinterpret_cast< const CvDetector::FeatureType(*)>(_a[1]))); break;
        case 10: _t->descriptorTypeChanged((*reinterpret_cast< const CvDetector::DescriptorExtractorType(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 11: _t->matchingStateChanged((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 12: _t->matcherTypeChanged((*reinterpret_cast< const CvMatcher::MatcherType(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 13: _t->matcherModeChanged((*reinterpret_cast< const CvMatcher::MatchType(*)>(_a[1]))); break;
        case 14: _t->knnChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 15: _t->radiusThresholdChanged((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 16: _t->registeringStateChanged((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 17: _t->poseComputingStateChanged((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 18: _t->printSizeChanged((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 19: _t->reprojThresholdChanged((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 20: _t->showModelFrameChanged((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 21: _t->showModelBoxChanged((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 22: _t->usePreviousPoseStateChanged((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 23: _t->cameraParametersChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 24: _t->setupProcessorfromUI(); break;
        case 25: _t->on_actionCamera_0_triggered(); break;
        case 26: _t->on_actionCamera_1_triggered(); break;
        case 27: _t->on_actionFile_triggered(); break;
        case 28: _t->on_actionModel_triggered(); break;
        case 29: _t->on_actionCalibData_triggered(); break;
        case 30: _t->on_actionQuit_triggered(); break;
        case 31: _t->on_actionFlip_triggered(); break;
        case 32: _t->on_actionGray_triggered(); break;
        case 33: _t->on_actionOriginalSize_triggered(); break;
        case 34: _t->on_actionConstrainedSize_triggered(); break;
        case 35: _t->on_actionRenderImage_triggered(); break;
        case 36: _t->on_actionRenderPixmap_triggered(); break;
        case 37: _t->on_actionRenderOpenGL_triggered(); break;
        case 38: _t->on_radioButtonOrigSize_clicked(); break;
        case 39: _t->on_radioButtonCustomSize_clicked(); break;
        case 40: _t->on_spinBoxWidth_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 41: _t->on_spinBoxHeight_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 42: _t->on_checkBoxFlip_clicked(); break;
        case 43: _t->on_checkBoxGray_clicked(); break;
        case 44: _t->on_groupBoxDetector_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 45: _t->on_groupBoxMatcher_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 46: _t->on_groupBoxRegistrar_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 47: _t->on_comboBoxFeatures_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 48: _t->on_comboBoxDescriptors_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 49: _t->on_comboBoxShowKPts_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 50: _t->on_comboBoxMatcherType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 51: _t->on_comboBoxMatcherMode_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 52: _t->on_spinBoxKnn_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 53: _t->on_doubleSpinBoxRadius_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 54: _t->on_doubleSpinBoxPrintSize_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 55: _t->on_doubleSpinBoxReprojThres_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 56: _t->on_checkBoxShowFrame_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 57: _t->on_checkBoxShowModelBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 58: _t->on_checkBoxUsePreviousPose_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 59: _t->on_comboBoxTimeUnit_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(const QString & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::sendMessage)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const QSize & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::sizeChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const int , const unsigned int , const unsigned int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::deviceChanged)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const QString & , const unsigned int , const unsigned int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::fileChanged)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::flipChanged)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::grayChanged)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::timePerFeatureStateChanged)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::detectingStateChanged)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const CvDetector::FeatureType );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::featureTypeChanged)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const CvDetector::DescriptorExtractorType , const bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::descriptorTypeChanged)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::matchingStateChanged)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const CvMatcher::MatcherType , const bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::matcherTypeChanged)) {
                *result = 12;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const CvMatcher::MatchType );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::matcherModeChanged)) {
                *result = 13;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::knnChanged)) {
                *result = 14;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::radiusThresholdChanged)) {
                *result = 15;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::registeringStateChanged)) {
                *result = 16;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::poseComputingStateChanged)) {
                *result = 17;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::printSizeChanged)) {
                *result = 18;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::reprojThresholdChanged)) {
                *result = 19;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::showModelFrameChanged)) {
                *result = 20;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::showModelBoxChanged)) {
                *result = 21;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::usePreviousPoseStateChanged)) {
                *result = 22;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::cameraParametersChanged)) {
                *result = 23;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 60)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 60;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 60)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 60;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::sendMessage(const QString & _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void MainWindow::sizeChanged(const QSize & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::deviceChanged(const int _t1, const unsigned int _t2, const unsigned int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::fileChanged(const QString & _t1, const unsigned int _t2, const unsigned int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::flipChanged(const bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MainWindow::grayChanged(const bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MainWindow::timePerFeatureStateChanged(const bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MainWindow::detectingStateChanged(const bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void MainWindow::featureTypeChanged(const CvDetector::FeatureType _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void MainWindow::descriptorTypeChanged(const CvDetector::DescriptorExtractorType _t1, const bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void MainWindow::matchingStateChanged(const bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void MainWindow::matcherTypeChanged(const CvMatcher::MatcherType _t1, const bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void MainWindow::matcherModeChanged(const CvMatcher::MatchType _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void MainWindow::knnChanged(const int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void MainWindow::radiusThresholdChanged(const double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void MainWindow::registeringStateChanged(const bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void MainWindow::poseComputingStateChanged(const bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void MainWindow::printSizeChanged(const double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void MainWindow::reprojThresholdChanged(const double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void MainWindow::showModelFrameChanged(const bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void MainWindow::showModelBoxChanged(const bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void MainWindow::usePreviousPoseStateChanged(const bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void MainWindow::cameraParametersChanged(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}
QT_END_MOC_NAMESPACE
