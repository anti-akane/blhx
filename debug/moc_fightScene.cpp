/****************************************************************************
** Meta object code from reading C++ file 'fightScene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../fightScene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fightScene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_fightScene_t {
    QByteArrayData data[8];
    char stringdata0[65];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_fightScene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_fightScene_t qt_meta_stringdata_fightScene = {
    {
QT_MOC_LITERAL(0, 0, 10), // "fightScene"
QT_MOC_LITERAL(1, 11, 10), // "closeFight"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 4), // "fail"
QT_MOC_LITERAL(4, 28, 7), // "succeed"
QT_MOC_LITERAL(5, 36, 15), // "callquitmessage"
QT_MOC_LITERAL(6, 52, 4), // "torp"
QT_MOC_LITERAL(7, 57, 7) // "airraid"

    },
    "fightScene\0closeFight\0\0fail\0succeed\0"
    "callquitmessage\0torp\0airraid"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_fightScene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void fightScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        fightScene *_t = static_cast<fightScene *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->closeFight(); break;
        case 1: _t->fail(); break;
        case 2: _t->succeed(); break;
        case 3: _t->callquitmessage(); break;
        case 4: _t->torp(); break;
        case 5: _t->airraid(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (fightScene::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&fightScene::closeFight)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (fightScene::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&fightScene::fail)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (fightScene::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&fightScene::succeed)) {
                *result = 2;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject fightScene::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_fightScene.data,
      qt_meta_data_fightScene,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *fightScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *fightScene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_fightScene.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int fightScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void fightScene::closeFight()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void fightScene::fail()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void fightScene::succeed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
