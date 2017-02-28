/****************************************************************************
** Meta object code from reading C++ file 'KnockPadMainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../KnockPad/KnockPadMainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KnockPadMainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KnockPadMainWindow_t {
    QByteArrayData data[18];
    char stringdata[219];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_KnockPadMainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_KnockPadMainWindow_t qt_meta_stringdata_KnockPadMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 13),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 12),
QT_MOC_LITERAL(4, 47, 17),
QT_MOC_LITERAL(5, 65, 12),
QT_MOC_LITERAL(6, 78, 14),
QT_MOC_LITERAL(7, 93, 7),
QT_MOC_LITERAL(8, 101, 8),
QT_MOC_LITERAL(9, 110, 9),
QT_MOC_LITERAL(10, 120, 10),
QT_MOC_LITERAL(11, 131, 14),
QT_MOC_LITERAL(12, 146, 14),
QT_MOC_LITERAL(13, 161, 11),
QT_MOC_LITERAL(14, 173, 13),
QT_MOC_LITERAL(15, 187, 13),
QT_MOC_LITERAL(16, 201, 8),
QT_MOC_LITERAL(17, 210, 7)
    },
    "KnockPadMainWindow\0createNewFile\0\0"
    "showOpenMenu\0saveInCurrentFile\0"
    "showSaveMenu\0openRecentFile\0cutText\0"
    "copyText\0pasteText\0deleteText\0"
    "changeFontType\0changeFontSize\0setBoldText\0"
    "setItalicText\0slotActivated\0QAction*\0"
    "pAction\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KnockPadMainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x0a,
       3,    0,   85,    2, 0x0a,
       4,    0,   86,    2, 0x0a,
       5,    0,   87,    2, 0x0a,
       6,    0,   88,    2, 0x0a,
       7,    0,   89,    2, 0x0a,
       8,    0,   90,    2, 0x0a,
       9,    0,   91,    2, 0x0a,
      10,    0,   92,    2, 0x0a,
      11,    0,   93,    2, 0x0a,
      12,    0,   94,    2, 0x0a,
      13,    0,   95,    2, 0x0a,
      14,    0,   96,    2, 0x0a,
      15,    1,   97,    2, 0x0a,

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
    QMetaType::Void, 0x80000000 | 16,   17,

       0        // eod
};

void KnockPadMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KnockPadMainWindow *_t = static_cast<KnockPadMainWindow *>(_o);
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
        case 13: _t->slotActivated((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    }
}

const QMetaObject KnockPadMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_KnockPadMainWindow.data,
      qt_meta_data_KnockPadMainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *KnockPadMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KnockPadMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KnockPadMainWindow.stringdata))
        return static_cast<void*>(const_cast< KnockPadMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int KnockPadMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
