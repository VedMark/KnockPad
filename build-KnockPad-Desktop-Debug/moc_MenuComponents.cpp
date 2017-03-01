/****************************************************************************
** Meta object code from reading C++ file 'MenuComponents.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../KnockPad/MenuComponents.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MenuComponents.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MenuComponents_t {
    QByteArrayData data[15];
    char stringdata[184];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MenuComponents_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MenuComponents_t qt_meta_stringdata_MenuComponents = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 13),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 12),
QT_MOC_LITERAL(4, 43, 17),
QT_MOC_LITERAL(5, 61, 12),
QT_MOC_LITERAL(6, 74, 14),
QT_MOC_LITERAL(7, 89, 7),
QT_MOC_LITERAL(8, 97, 8),
QT_MOC_LITERAL(9, 106, 9),
QT_MOC_LITERAL(10, 116, 10),
QT_MOC_LITERAL(11, 127, 14),
QT_MOC_LITERAL(12, 142, 14),
QT_MOC_LITERAL(13, 157, 11),
QT_MOC_LITERAL(14, 169, 13)
    },
    "MenuComponents\0createNewFile\0\0"
    "showOpenMenu\0saveInCurrentFile\0"
    "showSaveMenu\0openRecentFile\0cutText\0"
    "copyText\0pasteText\0deleteText\0"
    "changeFontType\0changeFontSize\0setBoldText\0"
    "setItalicText\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MenuComponents[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a,
       3,    0,   80,    2, 0x0a,
       4,    0,   81,    2, 0x0a,
       5,    0,   82,    2, 0x0a,
       6,    0,   83,    2, 0x0a,
       7,    0,   84,    2, 0x0a,
       8,    0,   85,    2, 0x0a,
       9,    0,   86,    2, 0x0a,
      10,    0,   87,    2, 0x0a,
      11,    0,   88,    2, 0x0a,
      12,    0,   89,    2, 0x0a,
      13,    0,   90,    2, 0x0a,
      14,    0,   91,    2, 0x0a,

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

       0        // eod
};

void MenuComponents::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MenuComponents *_t = static_cast<MenuComponents *>(_o);
        switch (_id) {
        case 0: _t->createNewFile(); break;
        case 1: _t->showOpenMenu(); break;
        case 2: _t->saveInCurrentFile(); break;
        case 3: _t->showSaveMenu(); break;
        case 4: _t->openRecentFile(); break;
        case 5: _t->cutText(); break;
        case 6: _t->copyText(); break;
        case 7: _t->pasteText(); break;
        case 8: _t->deleteText(); break;
        case 9: _t->changeFontType(); break;
        case 10: _t->changeFontSize(); break;
        case 11: _t->setBoldText(); break;
        case 12: _t->setItalicText(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MenuComponents::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MenuComponents.data,
      qt_meta_data_MenuComponents,  qt_static_metacall, 0, 0}
};


const QMetaObject *MenuComponents::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MenuComponents::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MenuComponents.stringdata))
        return static_cast<void*>(const_cast< MenuComponents*>(this));
    return QWidget::qt_metacast(_clname);
}

int MenuComponents::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
