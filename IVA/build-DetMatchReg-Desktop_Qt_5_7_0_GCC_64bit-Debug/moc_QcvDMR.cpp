/****************************************************************************
** Meta object code from reading C++ file 'QcvDMR.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../DetMatchReg/QcvDMR.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QcvDMR.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QcvDMR_t {
    QByteArrayData data[74];
    char stringdata0[1221];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QcvDMR_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QcvDMR_t qt_meta_stringdata_QcvDMR = {
    {
QT_MOC_LITERAL(0, 0, 6), // "QcvDMR"
QT_MOC_LITERAL(1, 7, 12), // "modelUpdated"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 17), // "modelImageChanged"
QT_MOC_LITERAL(4, 39, 4), // "Mat*"
QT_MOC_LITERAL(5, 44, 5), // "image"
QT_MOC_LITERAL(6, 50, 32), // "updateModelKeypointsNumberString"
QT_MOC_LITERAL(7, 83, 12), // "numberString"
QT_MOC_LITERAL(8, 96, 32), // "updateSceneKeypointsNumberString"
QT_MOC_LITERAL(9, 129, 25), // "updateDetectionTimeString"
QT_MOC_LITERAL(10, 155, 26), // "updateExtractionTimeString"
QT_MOC_LITERAL(11, 182, 24), // "updateMatchingTimeString"
QT_MOC_LITERAL(12, 207, 28), // "updateRegistrationTimeString"
QT_MOC_LITERAL(13, 236, 31), // "updateMatchedPointsNumberString"
QT_MOC_LITERAL(14, 268, 29), // "updateMeanMatchDistanceString"
QT_MOC_LITERAL(15, 298, 31), // "updateMinMaxMatchDistanceString"
QT_MOC_LITERAL(16, 330, 28), // "updateMaxMatchDistanceString"
QT_MOC_LITERAL(17, 359, 28), // "updateStdMatchDistanceString"
QT_MOC_LITERAL(18, 388, 29), // "updateReprojectionErrorString"
QT_MOC_LITERAL(19, 418, 25), // "updateInliersNumberString"
QT_MOC_LITERAL(20, 444, 6), // "update"
QT_MOC_LITERAL(21, 451, 14), // "setSourceImage"
QT_MOC_LITERAL(22, 466, 16), // "updateModelImage"
QT_MOC_LITERAL(23, 483, 6), // "string"
QT_MOC_LITERAL(24, 490, 8), // "filename"
QT_MOC_LITERAL(25, 499, 19), // "setCameraParameters"
QT_MOC_LITERAL(26, 519, 14), // "setFeatureType"
QT_MOC_LITERAL(27, 534, 23), // "CvDetector::FeatureType"
QT_MOC_LITERAL(28, 558, 11), // "featureType"
QT_MOC_LITERAL(29, 570, 26), // "setDescriptorExtractorType"
QT_MOC_LITERAL(30, 597, 35), // "CvDetector::DescriptorExtract..."
QT_MOC_LITERAL(31, 633, 14), // "descriptorType"
QT_MOC_LITERAL(32, 648, 12), // "checkMatcher"
QT_MOC_LITERAL(33, 661, 22), // "setModelDetectorUpdate"
QT_MOC_LITERAL(34, 684, 14), // "setMatcherType"
QT_MOC_LITERAL(35, 699, 22), // "CvMatcher::MatcherType"
QT_MOC_LITERAL(36, 722, 11), // "matcherType"
QT_MOC_LITERAL(37, 734, 16), // "checkDescriptors"
QT_MOC_LITERAL(38, 751, 14), // "setMatcherMode"
QT_MOC_LITERAL(39, 766, 20), // "CvMatcher::MatchType"
QT_MOC_LITERAL(40, 787, 11), // "matcherMode"
QT_MOC_LITERAL(41, 799, 6), // "setKnn"
QT_MOC_LITERAL(42, 806, 3), // "knn"
QT_MOC_LITERAL(43, 810, 18), // "setRadiusThreshold"
QT_MOC_LITERAL(44, 829, 15), // "radiusThreshold"
QT_MOC_LITERAL(45, 845, 18), // "setReprojThreshold"
QT_MOC_LITERAL(46, 864, 15), // "reprojThreshold"
QT_MOC_LITERAL(47, 880, 12), // "setPrintSize"
QT_MOC_LITERAL(48, 893, 9), // "printSize"
QT_MOC_LITERAL(49, 903, 14), // "setComputePose"
QT_MOC_LITERAL(50, 918, 11), // "computePose"
QT_MOC_LITERAL(51, 930, 18), // "setUsePreviousPose"
QT_MOC_LITERAL(52, 949, 3), // "use"
QT_MOC_LITERAL(53, 953, 12), // "setDetecting"
QT_MOC_LITERAL(54, 966, 9), // "detecting"
QT_MOC_LITERAL(55, 976, 11), // "setMatching"
QT_MOC_LITERAL(56, 988, 8), // "matching"
QT_MOC_LITERAL(57, 997, 14), // "setRegistering"
QT_MOC_LITERAL(58, 1012, 11), // "registering"
QT_MOC_LITERAL(59, 1024, 15), // "setVerboseLevel"
QT_MOC_LITERAL(60, 1040, 12), // "VerboseLevel"
QT_MOC_LITERAL(61, 1053, 5), // "level"
QT_MOC_LITERAL(62, 1059, 16), // "setKeyPointsMode"
QT_MOC_LITERAL(63, 1076, 12), // "KeyPointShow"
QT_MOC_LITERAL(64, 1089, 4), // "mode"
QT_MOC_LITERAL(65, 1094, 17), // "setShowModelFrame"
QT_MOC_LITERAL(66, 1112, 14), // "showModelFrame"
QT_MOC_LITERAL(67, 1127, 15), // "setShowModelBox"
QT_MOC_LITERAL(68, 1143, 12), // "showModelBox"
QT_MOC_LITERAL(69, 1156, 12), // "setBoxHeight"
QT_MOC_LITERAL(70, 1169, 6), // "height"
QT_MOC_LITERAL(71, 1176, 17), // "setTimePerFeature"
QT_MOC_LITERAL(72, 1194, 5), // "value"
QT_MOC_LITERAL(73, 1200, 20) // "resetMeanProcessTime"

    },
    "QcvDMR\0modelUpdated\0\0modelImageChanged\0"
    "Mat*\0image\0updateModelKeypointsNumberString\0"
    "numberString\0updateSceneKeypointsNumberString\0"
    "updateDetectionTimeString\0"
    "updateExtractionTimeString\0"
    "updateMatchingTimeString\0"
    "updateRegistrationTimeString\0"
    "updateMatchedPointsNumberString\0"
    "updateMeanMatchDistanceString\0"
    "updateMinMaxMatchDistanceString\0"
    "updateMaxMatchDistanceString\0"
    "updateStdMatchDistanceString\0"
    "updateReprojectionErrorString\0"
    "updateInliersNumberString\0update\0"
    "setSourceImage\0updateModelImage\0string\0"
    "filename\0setCameraParameters\0"
    "setFeatureType\0CvDetector::FeatureType\0"
    "featureType\0setDescriptorExtractorType\0"
    "CvDetector::DescriptorExtractorType\0"
    "descriptorType\0checkMatcher\0"
    "setModelDetectorUpdate\0setMatcherType\0"
    "CvMatcher::MatcherType\0matcherType\0"
    "checkDescriptors\0setMatcherMode\0"
    "CvMatcher::MatchType\0matcherMode\0"
    "setKnn\0knn\0setRadiusThreshold\0"
    "radiusThreshold\0setReprojThreshold\0"
    "reprojThreshold\0setPrintSize\0printSize\0"
    "setComputePose\0computePose\0"
    "setUsePreviousPose\0use\0setDetecting\0"
    "detecting\0setMatching\0matching\0"
    "setRegistering\0registering\0setVerboseLevel\0"
    "VerboseLevel\0level\0setKeyPointsMode\0"
    "KeyPointShow\0mode\0setShowModelFrame\0"
    "showModelFrame\0setShowModelBox\0"
    "showModelBox\0setBoxHeight\0height\0"
    "setTimePerFeature\0value\0resetMeanProcessTime"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QcvDMR[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      42,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      15,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  224,    2, 0x06 /* Public */,
       3,    1,  225,    2, 0x06 /* Public */,
       6,    1,  228,    2, 0x06 /* Public */,
       8,    1,  231,    2, 0x06 /* Public */,
       9,    1,  234,    2, 0x06 /* Public */,
      10,    1,  237,    2, 0x06 /* Public */,
      11,    1,  240,    2, 0x06 /* Public */,
      12,    1,  243,    2, 0x06 /* Public */,
      13,    1,  246,    2, 0x06 /* Public */,
      14,    1,  249,    2, 0x06 /* Public */,
      15,    1,  252,    2, 0x06 /* Public */,
      16,    1,  255,    2, 0x06 /* Public */,
      17,    1,  258,    2, 0x06 /* Public */,
      18,    1,  261,    2, 0x06 /* Public */,
      19,    1,  264,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      20,    0,  267,    2, 0x0a /* Public */,
      21,    1,  268,    2, 0x0a /* Public */,
      22,    1,  271,    2, 0x0a /* Public */,
      25,    1,  274,    2, 0x0a /* Public */,
      26,    1,  277,    2, 0x0a /* Public */,
      29,    2,  280,    2, 0x0a /* Public */,
      29,    1,  285,    2, 0x2a /* Public | MethodCloned */,
      33,    0,  288,    2, 0x0a /* Public */,
      34,    2,  289,    2, 0x0a /* Public */,
      34,    1,  294,    2, 0x2a /* Public | MethodCloned */,
      38,    1,  297,    2, 0x0a /* Public */,
      41,    1,  300,    2, 0x0a /* Public */,
      43,    1,  303,    2, 0x0a /* Public */,
      45,    1,  306,    2, 0x0a /* Public */,
      47,    1,  309,    2, 0x0a /* Public */,
      49,    1,  312,    2, 0x0a /* Public */,
      51,    1,  315,    2, 0x0a /* Public */,
      53,    1,  318,    2, 0x0a /* Public */,
      55,    1,  321,    2, 0x0a /* Public */,
      57,    1,  324,    2, 0x0a /* Public */,
      59,    1,  327,    2, 0x0a /* Public */,
      62,    1,  330,    2, 0x0a /* Public */,
      65,    1,  333,    2, 0x0a /* Public */,
      67,    1,  336,    2, 0x0a /* Public */,
      69,    1,  339,    2, 0x0a /* Public */,
      71,    1,  342,    2, 0x0a /* Public */,
      73,    0,  345,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 23,   24,
    QMetaType::Void, 0x80000000 | 23,   24,
    QMetaType::Void, 0x80000000 | 27,   28,
    QMetaType::Void, 0x80000000 | 30, QMetaType::Bool,   31,   32,
    QMetaType::Void, 0x80000000 | 30,   31,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 35, QMetaType::Bool,   36,   37,
    QMetaType::Void, 0x80000000 | 35,   36,
    QMetaType::Void, 0x80000000 | 39,   40,
    QMetaType::Void, QMetaType::Int,   42,
    QMetaType::Void, QMetaType::Double,   44,
    QMetaType::Void, QMetaType::Double,   46,
    QMetaType::Bool, QMetaType::Double,   48,
    QMetaType::Bool, QMetaType::Bool,   50,
    QMetaType::Void, QMetaType::Bool,   52,
    QMetaType::Void, QMetaType::Bool,   54,
    QMetaType::Bool, QMetaType::Bool,   56,
    QMetaType::Bool, QMetaType::Bool,   58,
    QMetaType::Void, 0x80000000 | 60,   61,
    QMetaType::Void, 0x80000000 | 63,   64,
    QMetaType::Bool, QMetaType::Bool,   66,
    QMetaType::Bool, QMetaType::Bool,   68,
    QMetaType::Void, QMetaType::Double,   70,
    QMetaType::Void, QMetaType::Bool,   72,
    QMetaType::Void,

       0        // eod
};

void QcvDMR::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QcvDMR *_t = static_cast<QcvDMR *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->modelUpdated(); break;
        case 1: _t->modelImageChanged((*reinterpret_cast< Mat*(*)>(_a[1]))); break;
        case 2: _t->updateModelKeypointsNumberString((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->updateSceneKeypointsNumberString((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->updateDetectionTimeString((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->updateExtractionTimeString((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->updateMatchingTimeString((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->updateRegistrationTimeString((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->updateMatchedPointsNumberString((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->updateMeanMatchDistanceString((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->updateMinMaxMatchDistanceString((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->updateMaxMatchDistanceString((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->updateStdMatchDistanceString((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->updateReprojectionErrorString((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->updateInliersNumberString((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->update(); break;
        case 16: _t->setSourceImage((*reinterpret_cast< Mat*(*)>(_a[1]))); break;
        case 17: _t->updateModelImage((*reinterpret_cast< const string(*)>(_a[1]))); break;
        case 18: _t->setCameraParameters((*reinterpret_cast< const string(*)>(_a[1]))); break;
        case 19: _t->setFeatureType((*reinterpret_cast< const CvDetector::FeatureType(*)>(_a[1]))); break;
        case 20: _t->setDescriptorExtractorType((*reinterpret_cast< const CvDetector::DescriptorExtractorType(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 21: _t->setDescriptorExtractorType((*reinterpret_cast< const CvDetector::DescriptorExtractorType(*)>(_a[1]))); break;
        case 22: _t->setModelDetectorUpdate(); break;
        case 23: _t->setMatcherType((*reinterpret_cast< const CvMatcher::MatcherType(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 24: _t->setMatcherType((*reinterpret_cast< const CvMatcher::MatcherType(*)>(_a[1]))); break;
        case 25: _t->setMatcherMode((*reinterpret_cast< const CvMatcher::MatchType(*)>(_a[1]))); break;
        case 26: _t->setKnn((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 27: _t->setRadiusThreshold((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 28: _t->setReprojThreshold((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 29: { bool _r = _t->setPrintSize((*reinterpret_cast< const double(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 30: { bool _r = _t->setComputePose((*reinterpret_cast< const bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 31: _t->setUsePreviousPose((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 32: _t->setDetecting((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 33: { bool _r = _t->setMatching((*reinterpret_cast< const bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 34: { bool _r = _t->setRegistering((*reinterpret_cast< const bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 35: _t->setVerboseLevel((*reinterpret_cast< const VerboseLevel(*)>(_a[1]))); break;
        case 36: _t->setKeyPointsMode((*reinterpret_cast< const KeyPointShow(*)>(_a[1]))); break;
        case 37: { bool _r = _t->setShowModelFrame((*reinterpret_cast< const bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 38: { bool _r = _t->setShowModelBox((*reinterpret_cast< const bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 39: _t->setBoxHeight((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 40: _t->setTimePerFeature((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 41: _t->resetMeanProcessTime(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QcvDMR::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvDMR::modelUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QcvDMR::*_t)(Mat * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvDMR::modelImageChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QcvDMR::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvDMR::updateModelKeypointsNumberString)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QcvDMR::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvDMR::updateSceneKeypointsNumberString)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (QcvDMR::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvDMR::updateDetectionTimeString)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (QcvDMR::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvDMR::updateExtractionTimeString)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (QcvDMR::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvDMR::updateMatchingTimeString)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (QcvDMR::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvDMR::updateRegistrationTimeString)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (QcvDMR::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvDMR::updateMatchedPointsNumberString)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (QcvDMR::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvDMR::updateMeanMatchDistanceString)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (QcvDMR::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvDMR::updateMinMaxMatchDistanceString)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (QcvDMR::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvDMR::updateMaxMatchDistanceString)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (QcvDMR::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvDMR::updateStdMatchDistanceString)) {
                *result = 12;
                return;
            }
        }
        {
            typedef void (QcvDMR::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvDMR::updateReprojectionErrorString)) {
                *result = 13;
                return;
            }
        }
        {
            typedef void (QcvDMR::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QcvDMR::updateInliersNumberString)) {
                *result = 14;
                return;
            }
        }
    }
}

const QMetaObject QcvDMR::staticMetaObject = {
    { &QcvProcessor::staticMetaObject, qt_meta_stringdata_QcvDMR.data,
      qt_meta_data_QcvDMR,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QcvDMR::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QcvDMR::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QcvDMR.stringdata0))
        return static_cast<void*>(const_cast< QcvDMR*>(this));
    if (!strcmp(_clname, "CvDMR"))
        return static_cast< CvDMR*>(const_cast< QcvDMR*>(this));
    return QcvProcessor::qt_metacast(_clname);
}

int QcvDMR::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QcvProcessor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 42)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 42;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 42)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 42;
    }
    return _id;
}

// SIGNAL 0
void QcvDMR::modelUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void QcvDMR::modelImageChanged(Mat * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QcvDMR::updateModelKeypointsNumberString(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QcvDMR::updateSceneKeypointsNumberString(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QcvDMR::updateDetectionTimeString(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QcvDMR::updateExtractionTimeString(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QcvDMR::updateMatchingTimeString(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QcvDMR::updateRegistrationTimeString(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void QcvDMR::updateMatchedPointsNumberString(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void QcvDMR::updateMeanMatchDistanceString(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void QcvDMR::updateMinMaxMatchDistanceString(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void QcvDMR::updateMaxMatchDistanceString(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void QcvDMR::updateStdMatchDistanceString(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void QcvDMR::updateReprojectionErrorString(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void QcvDMR::updateInliersNumberString(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}
QT_END_MOC_NAMESPACE
