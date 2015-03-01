/****************************************************************************
** Meta object code from reading C++ file 'newarticleworkspacewindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LuD/newarticleworkspacewindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'newarticleworkspacewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_newArticleWorkspaceWindow_t {
    QByteArrayData data[10];
    char stringdata[259];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_newArticleWorkspaceWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_newArticleWorkspaceWindow_t qt_meta_stringdata_newArticleWorkspaceWindow = {
    {
QT_MOC_LITERAL(0, 0, 25), // "newArticleWorkspaceWindow"
QT_MOC_LITERAL(1, 26, 32), // "on_chooseFile_pushButton_clicked"
QT_MOC_LITERAL(2, 59, 0), // ""
QT_MOC_LITERAL(3, 60, 28), // "on_submit_pushButton_clicked"
QT_MOC_LITERAL(4, 89, 30), // "on_addImage_pushButton_clicked"
QT_MOC_LITERAL(5, 120, 28), // "on_delete_pushButton_pressed"
QT_MOC_LITERAL(6, 149, 33), // "on_copyHistory_pushButton_cli..."
QT_MOC_LITERAL(7, 183, 38), // "on_sectionComboBox_currentInd..."
QT_MOC_LITERAL(8, 222, 4), // "arg1"
QT_MOC_LITERAL(9, 227, 31) // "on_deleteAWS_pushButton_clicked"

    },
    "newArticleWorkspaceWindow\0"
    "on_chooseFile_pushButton_clicked\0\0"
    "on_submit_pushButton_clicked\0"
    "on_addImage_pushButton_clicked\0"
    "on_delete_pushButton_pressed\0"
    "on_copyHistory_pushButton_clicked\0"
    "on_sectionComboBox_currentIndexChanged\0"
    "arg1\0on_deleteAWS_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_newArticleWorkspaceWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    1,   54,    2, 0x08 /* Private */,
       9,    0,   57,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,

       0        // eod
};

void newArticleWorkspaceWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        newArticleWorkspaceWindow *_t = static_cast<newArticleWorkspaceWindow *>(_o);
        switch (_id) {
        case 0: _t->on_chooseFile_pushButton_clicked(); break;
        case 1: _t->on_submit_pushButton_clicked(); break;
        case 2: _t->on_addImage_pushButton_clicked(); break;
        case 3: _t->on_delete_pushButton_pressed(); break;
        case 4: _t->on_copyHistory_pushButton_clicked(); break;
        case 5: _t->on_sectionComboBox_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_deleteAWS_pushButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject newArticleWorkspaceWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_newArticleWorkspaceWindow.data,
      qt_meta_data_newArticleWorkspaceWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *newArticleWorkspaceWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *newArticleWorkspaceWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_newArticleWorkspaceWindow.stringdata))
        return static_cast<void*>(const_cast< newArticleWorkspaceWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int newArticleWorkspaceWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
