/****************************************************************************
** Meta object code from reading C++ file 'framehandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "framehandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'framehandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FrameHandler_t {
    QByteArrayData data[15];
    char stringdata0[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FrameHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FrameHandler_t qt_meta_stringdata_FrameHandler = {
    {
QT_MOC_LITERAL(0, 0, 12), // "FrameHandler"
QT_MOC_LITERAL(1, 13, 15), // "changeImageView"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 11), // "imageSource"
QT_MOC_LITERAL(4, 42, 18), // "changeImageViewErm"
QT_MOC_LITERAL(5, 61, 6), // "toggle"
QT_MOC_LITERAL(6, 68, 12), // "frameChanged"
QT_MOC_LITERAL(7, 81, 10), // "jFrameSize"
QT_MOC_LITERAL(8, 92, 11), // "ChangeFrame"
QT_MOC_LITERAL(9, 104, 7), // "layerno"
QT_MOC_LITERAL(10, 112, 10), // "ShiftImage"
QT_MOC_LITERAL(11, 123, 8), // "__Job3D*"
QT_MOC_LITERAL(12, 132, 7), // "jobData"
QT_MOC_LITERAL(13, 140, 5), // "char*"
QT_MOC_LITERAL(14, 146, 8) // "tmpImage"

    },
    "FrameHandler\0changeImageView\0\0imageSource\0"
    "changeImageViewErm\0toggle\0frameChanged\0"
    "jFrameSize\0ChangeFrame\0layerno\0"
    "ShiftImage\0__Job3D*\0jobData\0char*\0"
    "tmpImage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FrameHandler[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    2,   37,    2, 0x06 /* Public */,
       6,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    4,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    3,    5,
    QMetaType::Void, QMetaType::Int,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, 0x80000000 | 11, 0x80000000 | 13,    9,   10,   12,   14,

       0        // eod
};

void FrameHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FrameHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeImageView((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->changeImageViewErm((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->ChangeFrame((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< __Job3D*(*)>(_a[3])),(*reinterpret_cast< char*(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FrameHandler::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FrameHandler::changeImageView)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FrameHandler::*)(QString , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FrameHandler::changeImageViewErm)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FrameHandler::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FrameHandler::frameChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FrameHandler::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_FrameHandler.data,
    qt_meta_data_FrameHandler,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FrameHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FrameHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FrameHandler.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FrameHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void FrameHandler::changeImageView(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FrameHandler::changeImageViewErm(QString _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FrameHandler::frameChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE