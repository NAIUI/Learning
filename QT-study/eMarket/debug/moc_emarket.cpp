/****************************************************************************
** Meta object code from reading C++ file 'emarket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../emarket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'emarket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_eMarket_t {
    QByteArrayData data[10];
    char stringdata0[221];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_eMarket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_eMarket_t qt_meta_stringdata_eMarket = {
    {
QT_MOC_LITERAL(0, 0, 7), // "eMarket"
QT_MOC_LITERAL(1, 8, 29), // "on_commodityTableView_clicked"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 11), // "QModelIndex"
QT_MOC_LITERAL(4, 51, 5), // "index"
QT_MOC_LITERAL(5, 57, 28), // "on_preSellPushButton_clicked"
QT_MOC_LITERAL(6, 86, 34), // "on_prePlaceOrderPushButton_cl..."
QT_MOC_LITERAL(7, 121, 30), // "on_newUploadPushButton_clicked"
QT_MOC_LITERAL(8, 152, 34), // "on_newPutinStorePushButton_cl..."
QT_MOC_LITERAL(9, 187, 33) // "on_newClearancePushButton_cli..."

    },
    "eMarket\0on_commodityTableView_clicked\0"
    "\0QModelIndex\0index\0on_preSellPushButton_clicked\0"
    "on_prePlaceOrderPushButton_clicked\0"
    "on_newUploadPushButton_clicked\0"
    "on_newPutinStorePushButton_clicked\0"
    "on_newClearancePushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_eMarket[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,
       8,    0,   50,    2, 0x08 /* Private */,
       9,    0,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void eMarket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<eMarket *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_commodityTableView_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->on_preSellPushButton_clicked(); break;
        case 2: _t->on_prePlaceOrderPushButton_clicked(); break;
        case 3: _t->on_newUploadPushButton_clicked(); break;
        case 4: _t->on_newPutinStorePushButton_clicked(); break;
        case 5: _t->on_newClearancePushButton_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject eMarket::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_eMarket.data,
    qt_meta_data_eMarket,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *eMarket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *eMarket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_eMarket.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int eMarket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
