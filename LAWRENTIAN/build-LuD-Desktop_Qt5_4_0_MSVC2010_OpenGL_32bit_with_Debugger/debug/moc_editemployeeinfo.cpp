/****************************************************************************
** Meta object code from reading C++ file 'editemployeeinfo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LuD/editemployeeinfo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editemployeeinfo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EditEmployeeInfo_t {
    QByteArrayData data[7];
    char stringdata[147];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EditEmployeeInfo_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EditEmployeeInfo_t qt_meta_stringdata_EditEmployeeInfo = {
    {
QT_MOC_LITERAL(0, 0, 16), // "EditEmployeeInfo"
QT_MOC_LITERAL(1, 17, 35), // "on_nameComboBox_currentIndexC..."
QT_MOC_LITERAL(2, 53, 0), // ""
QT_MOC_LITERAL(3, 54, 5), // "index"
QT_MOC_LITERAL(4, 60, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(5, 82, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(6, 106, 40) // "on_probationComboBox_currentI..."

    },
    "EditEmployeeInfo\0on_nameComboBox_currentIndexChanged\0"
    "\0index\0on_pushButton_clicked\0"
    "on_pushButton_2_clicked\0"
    "on_probationComboBox_currentIndexChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditEmployeeInfo[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x08 /* Private */,
       4,    0,   37,    2, 0x08 /* Private */,
       5,    0,   38,    2, 0x08 /* Private */,
       6,    1,   39,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void EditEmployeeInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EditEmployeeInfo *_t = static_cast<EditEmployeeInfo *>(_o);
        switch (_id) {
        case 0: _t->on_nameComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_pushButton_clicked(); break;
        case 2: _t->on_pushButton_2_clicked(); break;
        case 3: _t->on_probationComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject EditEmployeeInfo::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_EditEmployeeInfo.data,
      qt_meta_data_EditEmployeeInfo,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EditEmployeeInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditEmployeeInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EditEmployeeInfo.stringdata))
        return static_cast<void*>(const_cast< EditEmployeeInfo*>(this));
    return QDialog::qt_metacast(_clname);
}

int EditEmployeeInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
