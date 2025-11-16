/****************************************************************************
** Meta object code from reading C++ file 'winleft.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../winleft.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'winleft.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WinLeft_t {
    QByteArrayData data[16];
    char stringdata0[241];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WinLeft_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WinLeft_t qt_meta_stringdata_WinLeft = {
    {
QT_MOC_LITERAL(0, 0, 7), // "WinLeft"
QT_MOC_LITERAL(1, 8, 10), // "BT_Pressed"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 4), // "flat"
QT_MOC_LITERAL(4, 25, 18), // "on_BT_Flip_clicked"
QT_MOC_LITERAL(5, 44, 20), // "on_BT_Mirror_clicked"
QT_MOC_LITERAL(6, 65, 18), // "on_BT_Menu_clicked"
QT_MOC_LITERAL(7, 84, 18), // "on_BT_HOME_clicked"
QT_MOC_LITERAL(8, 103, 16), // "on_BT_AI_clicked"
QT_MOC_LITERAL(9, 120, 18), // "on_BT_PUSH_clicked"
QT_MOC_LITERAL(10, 139, 19), // "on_BT_Reset_clicked"
QT_MOC_LITERAL(11, 159, 16), // "on_Cb_WB_clicked"
QT_MOC_LITERAL(12, 176, 7), // "checked"
QT_MOC_LITERAL(13, 184, 16), // "on_BT_IR_clicked"
QT_MOC_LITERAL(14, 201, 17), // "on_BT_DAY_clicked"
QT_MOC_LITERAL(15, 219, 21) // "on_BT_RST_PTZ_clicked"

    },
    "WinLeft\0BT_Pressed\0\0flat\0on_BT_Flip_clicked\0"
    "on_BT_Mirror_clicked\0on_BT_Menu_clicked\0"
    "on_BT_HOME_clicked\0on_BT_AI_clicked\0"
    "on_BT_PUSH_clicked\0on_BT_Reset_clicked\0"
    "on_Cb_WB_clicked\0checked\0on_BT_IR_clicked\0"
    "on_BT_DAY_clicked\0on_BT_RST_PTZ_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WinLeft[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   77,    2, 0x08 /* Private */,
       5,    0,   78,    2, 0x08 /* Private */,
       6,    0,   79,    2, 0x08 /* Private */,
       7,    0,   80,    2, 0x08 /* Private */,
       8,    0,   81,    2, 0x08 /* Private */,
       9,    0,   82,    2, 0x08 /* Private */,
      10,    0,   83,    2, 0x08 /* Private */,
      11,    1,   84,    2, 0x08 /* Private */,
      13,    0,   87,    2, 0x08 /* Private */,
      14,    0,   88,    2, 0x08 /* Private */,
      15,    0,   89,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WinLeft::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WinLeft *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->BT_Pressed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_BT_Flip_clicked(); break;
        case 2: _t->on_BT_Mirror_clicked(); break;
        case 3: _t->on_BT_Menu_clicked(); break;
        case 4: _t->on_BT_HOME_clicked(); break;
        case 5: _t->on_BT_AI_clicked(); break;
        case 6: _t->on_BT_PUSH_clicked(); break;
        case 7: _t->on_BT_Reset_clicked(); break;
        case 8: _t->on_Cb_WB_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_BT_IR_clicked(); break;
        case 10: _t->on_BT_DAY_clicked(); break;
        case 11: _t->on_BT_RST_PTZ_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WinLeft::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WinLeft::BT_Pressed)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WinLeft::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_WinLeft.data,
    qt_meta_data_WinLeft,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WinLeft::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WinLeft::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WinLeft.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int WinLeft::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void WinLeft::BT_Pressed(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
