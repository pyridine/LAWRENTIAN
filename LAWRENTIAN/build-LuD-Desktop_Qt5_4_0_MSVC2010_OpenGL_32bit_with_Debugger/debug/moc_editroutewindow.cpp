/****************************************************************************
** Meta object code from reading C++ file 'editroutewindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LuD/editroutewindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editroutewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EditRouteWindow_t {
    QByteArrayData data[8];
    char stringdata[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EditRouteWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EditRouteWindow_t qt_meta_stringdata_EditRouteWindow = {
    {
QT_MOC_LITERAL(0, 0, 15), // "EditRouteWindow"
QT_MOC_LITERAL(1, 16, 19), // "on_upButton_clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 21), // "on_downButton_clicked"
QT_MOC_LITERAL(4, 59, 25), // "on_addPointButton_clicked"
QT_MOC_LITERAL(5, 85, 28), // "on_removePointButton_clicked"
QT_MOC_LITERAL(6, 114, 23), // "on_cancelButton_clicked"
QT_MOC_LITERAL(7, 138, 22) // "on_applyButton_clicked"

    },
    "EditRouteWindow\0on_upButton_clicked\0"
    "\0on_downButton_clicked\0on_addPointButton_clicked\0"
    "on_removePointButton_clicked\0"
    "on_cancelButton_clicked\0on_applyButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditRouteWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EditRouteWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EditRouteWindow *_t = static_cast<EditRouteWindow *>(_o);
        switch (_id) {
        case 0: _t->on_upButton_clicked(); break;
        case 1: _t->on_downButton_clicked(); break;
        case 2: _t->on_addPointButton_clicked(); break;
        case 3: _t->on_removePointButton_clicked(); break;
        case 4: _t->on_cancelButton_clicked(); break;
        case 5: _t->on_applyButton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject EditRouteWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_EditRouteWindow.data,
      qt_meta_data_EditRouteWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EditRouteWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditRouteWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EditRouteWindow.stringdata))
        return static_cast<void*>(const_cast< EditRouteWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int EditRouteWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
