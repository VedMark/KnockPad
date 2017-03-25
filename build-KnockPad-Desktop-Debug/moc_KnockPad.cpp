/****************************************************************************
** Meta object code from reading C++ file 'KnockPad.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../KnockPad/KnockPad.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KnockPad.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KnockPad_t {
    QByteArrayData data[17];
    char stringdata[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_KnockPad_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_KnockPad_t qt_meta_stringdata_KnockPad = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 7),
QT_MOC_LITERAL(2, 17, 0),
QT_MOC_LITERAL(3, 18, 4),
QT_MOC_LITERAL(4, 23, 4),
QT_MOC_LITERAL(5, 28, 6),
QT_MOC_LITERAL(6, 35, 8),
QT_MOC_LITERAL(7, 44, 17),
QT_MOC_LITERAL(8, 62, 14),
QT_MOC_LITERAL(9, 77, 7),
QT_MOC_LITERAL(10, 85, 8),
QT_MOC_LITERAL(11, 94, 9),
QT_MOC_LITERAL(12, 104, 10),
QT_MOC_LITERAL(13, 115, 14),
QT_MOC_LITERAL(14, 130, 14),
QT_MOC_LITERAL(15, 145, 11),
QT_MOC_LITERAL(16, 157, 13)
    },
    "KnockPad\0newFile\0\0open\0save\0saveAs\0"
    "closeApp\0saveInCurrentFile\0openRecentFile\0"
    "cutText\0copyText\0pasteText\0deleteText\0"
    "changeFontType\0changeFontSize\0setBoldText\0"
    "setItalicText\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KnockPad[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x0a,
       3,    0,   90,    2, 0x0a,
       4,    0,   91,    2, 0x0a,
       5,    0,   92,    2, 0x0a,
       6,    0,   93,    2, 0x0a,
       7,    0,   94,    2, 0x0a,
       8,    0,   95,    2, 0x0a,
       9,    0,   96,    2, 0x0a,
      10,    0,   97,    2, 0x0a,
      11,    0,   98,    2, 0x0a,
      12,    0,   99,    2, 0x0a,
      13,    0,  100,    2, 0x0a,
      14,    0,  101,    2, 0x0a,
      15,    0,  102,    2, 0x0a,
      16,    0,  103,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
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

void KnockPad::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KnockPad *_t = static_cast<KnockPad *>(_o);
        switch (_id) {
        case 0: _t->newFile(); break;
        case 1: _t->open(); break;
        case 2: { bool _r = _t->save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = _t->saveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: _t->closeApp(); break;
        case 5: _t->saveInCurrentFile(); break;
        case 6: _t->openRecentFile(); break;
        case 7: _t->cutText(); break;
        case 8: _t->copyText(); break;
        case 9: _t->pasteText(); break;
        case 10: _t->deleteText(); break;
        case 11: _t->changeFontType(); break;
        case 12: _t->changeFontSize(); break;
        case 13: _t->setBoldText(); break;
        case 14: _t->setItalicText(); break;
        default: ;
        }
    }
}

const QMetaObject KnockPad::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_KnockPad.data,
      qt_meta_data_KnockPad,  qt_static_metacall, 0, 0}
};


const QMetaObject *KnockPad::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KnockPad::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KnockPad.stringdata))
        return static_cast<void*>(const_cast< KnockPad*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int KnockPad::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
