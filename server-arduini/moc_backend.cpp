/****************************************************************************
** Meta object code from reading C++ file 'backend.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "backend.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'backend.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BackEnd_t {
    QByteArrayData data[32];
    char stringdata0[361];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BackEnd_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BackEnd_t qt_meta_stringdata_BackEnd = {
    {
QT_MOC_LITERAL(0, 0, 7), // "BackEnd"
QT_MOC_LITERAL(1, 8, 15), // "changeImageView"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 11), // "imageSource"
QT_MOC_LITERAL(4, 37, 18), // "changeImageViewErm"
QT_MOC_LITERAL(5, 56, 6), // "toggle"
QT_MOC_LITERAL(6, 63, 8), // "layerNum"
QT_MOC_LITERAL(7, 72, 18), // "changeFrameHandler"
QT_MOC_LITERAL(8, 91, 7), // "layerno"
QT_MOC_LITERAL(9, 99, 10), // "ShiftImage"
QT_MOC_LITERAL(10, 110, 8), // "__Job3D*"
QT_MOC_LITERAL(11, 119, 7), // "jobData"
QT_MOC_LITERAL(12, 127, 5), // "char*"
QT_MOC_LITERAL(13, 133, 8), // "tmpImage"
QT_MOC_LITERAL(14, 142, 10), // "sendQImage"
QT_MOC_LITERAL(15, 153, 4), // "flag"
QT_MOC_LITERAL(16, 158, 23), // "toggleImageVisiblityErm"
QT_MOC_LITERAL(17, 182, 18), // "imageInitializeErm"
QT_MOC_LITERAL(18, 201, 13), // "setPrintImage"
QT_MOC_LITERAL(19, 215, 10), // "printImage"
QT_MOC_LITERAL(20, 226, 18), // "moduleDistanceData"
QT_MOC_LITERAL(21, 245, 1), // "d"
QT_MOC_LITERAL(22, 247, 12), // "frameChanged"
QT_MOC_LITERAL(23, 260, 10), // "jFrameSize"
QT_MOC_LITERAL(24, 271, 12), // "getImageItem"
QT_MOC_LITERAL(25, 284, 11), // "addClientfd"
QT_MOC_LITERAL(26, 296, 8), // "clientfd"
QT_MOC_LITERAL(27, 305, 10), // "isPrinting"
QT_MOC_LITERAL(28, 316, 15), // "getImagePreview"
QT_MOC_LITERAL(29, 332, 12), // "setImageItem"
QT_MOC_LITERAL(30, 345, 10), // "ImageItem*"
QT_MOC_LITERAL(31, 356, 4) // "item"

    },
    "BackEnd\0changeImageView\0\0imageSource\0"
    "changeImageViewErm\0toggle\0layerNum\0"
    "changeFrameHandler\0layerno\0ShiftImage\0"
    "__Job3D*\0jobData\0char*\0tmpImage\0"
    "sendQImage\0flag\0toggleImageVisiblityErm\0"
    "imageInitializeErm\0setPrintImage\0"
    "printImage\0moduleDistanceData\0d\0"
    "frameChanged\0jFrameSize\0getImageItem\0"
    "addClientfd\0clientfd\0isPrinting\0"
    "getImagePreview\0setImageItem\0ImageItem*\0"
    "item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BackEnd[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       4,    3,   87,    2, 0x06 /* Public */,
       7,    4,   94,    2, 0x06 /* Public */,
      14,    2,  103,    2, 0x06 /* Public */,
      16,    0,  108,    2, 0x06 /* Public */,
      17,    0,  109,    2, 0x06 /* Public */,
      18,    1,  110,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      20,    1,  113,    2, 0x0a /* Public */,
      22,    1,  116,    2, 0x0a /* Public */,
      24,    1,  119,    2, 0x0a /* Public */,
      25,    1,  122,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      27,    0,  125,    2, 0x02 /* Public */,
      28,    0,  126,    2, 0x02 /* Public */,
      29,    1,  127,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Int,    3,    5,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, 0x80000000 | 10, 0x80000000 | 12,    8,    9,   11,   13,
    QMetaType::Void, QMetaType::QImage, QMetaType::QString,    3,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,   19,

 // slots: parameters
    QMetaType::Void, QMetaType::Float,   21,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void, QMetaType::QImage,   19,
    QMetaType::Void, QMetaType::Int,   26,

 // methods: parameters
    QMetaType::Bool,
    QMetaType::QString,
    QMetaType::Void, 0x80000000 | 30,   31,

       0        // eod
};

void BackEnd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BackEnd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeImageView((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->changeImageViewErm((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->changeFrameHandler((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< __Job3D*(*)>(_a[3])),(*reinterpret_cast< char*(*)>(_a[4]))); break;
        case 3: _t->sendQImage((*reinterpret_cast< QImage(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->toggleImageVisiblityErm(); break;
        case 5: _t->imageInitializeErm(); break;
        case 6: _t->setPrintImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 7: _t->moduleDistanceData((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->getImageItem((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 10: _t->addClientfd((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: { bool _r = _t->isPrinting();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 12: { QString _r = _t->getImagePreview();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->setImageItem((*reinterpret_cast< ImageItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ImageItem* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BackEnd::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::changeImageView)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BackEnd::*)(QString , bool , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::changeImageViewErm)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BackEnd::*)(int , bool , __Job3D * , char * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::changeFrameHandler)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (BackEnd::*)(QImage , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::sendQImage)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (BackEnd::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::toggleImageVisiblityErm)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (BackEnd::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::imageInitializeErm)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (BackEnd::*)(QImage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::setPrintImage)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BackEnd::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_BackEnd.data,
    qt_meta_data_BackEnd,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BackEnd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BackEnd::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BackEnd.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BackEnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void BackEnd::changeImageView(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BackEnd::changeImageViewErm(QString _t1, bool _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void BackEnd::changeFrameHandler(int _t1, bool _t2, __Job3D * _t3, char * _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void BackEnd::sendQImage(QImage _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void BackEnd::toggleImageVisiblityErm()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void BackEnd::imageInitializeErm()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void BackEnd::setPrintImage(QImage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
