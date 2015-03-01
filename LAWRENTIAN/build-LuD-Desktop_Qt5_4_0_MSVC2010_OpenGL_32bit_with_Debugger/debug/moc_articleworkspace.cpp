/****************************************************************************
** Meta object code from reading C++ file 'articleworkspace.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LuD/articleworkspace.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'articleworkspace.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_articleWorkspace_t {
    QByteArrayData data[7];
    char stringdata[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_articleWorkspace_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_articleWorkspace_t qt_meta_stringdata_articleWorkspace = {
    {
QT_MOC_LITERAL(0, 0, 16), // "articleWorkspace"
QT_MOC_LITERAL(1, 17, 41), // "on_addArticleWorkspace_pushBu..."
QT_MOC_LITERAL(2, 59, 0), // ""
QT_MOC_LITERAL(3, 60, 12), // "handleButton"
QT_MOC_LITERAL(4, 73, 20), // "openArticleWorkspace"
QT_MOC_LITERAL(5, 94, 8), // "Article*"
QT_MOC_LITERAL(6, 103, 1) // "a"

    },
    "articleWorkspace\0"
    "on_addArticleWorkspace_pushButton_clicked\0"
    "\0handleButton\0openArticleWorkspace\0"
    "Article*\0a"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_articleWorkspace[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    0,   30,    2, 0x08 /* Private */,
       4,    1,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void articleWorkspace::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        articleWorkspace *_t = static_cast<articleWorkspace *>(_o);
        switch (_id) {
        case 0: _t->on_addArticleWorkspace_pushButton_clicked(); break;
        case 1: _t->handleButton(); break;
        case 2: _t->openArticleWorkspace((*reinterpret_cast< Article*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject articleWorkspace::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_articleWorkspace.data,
      qt_meta_data_articleWorkspace,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *articleWorkspace::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *articleWorkspace::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_articleWorkspace.stringdata))
        return static_cast<void*>(const_cast< articleWorkspace*>(this));
    return QWidget::qt_metacast(_clname);
}

int articleWorkspace::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
