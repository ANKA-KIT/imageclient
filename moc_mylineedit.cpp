/****************************************************************************
** Meta object code from reading C++ file 'mylineedit.h'
**
** Created: Tue Aug 14 09:45:51 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mylineedit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mylineedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyLineEdit[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      24,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,   40,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyLineEdit[] = {
    "MyLineEdit\0\0setVal(int)\0setValD(double)\0"
    "event\0keyPressEvent(QKeyEvent*)\0"
};

void MyLineEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyLineEdit *_t = static_cast<MyLineEdit *>(_o);
        switch (_id) {
        case 0: _t->setVal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setValD((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MyLineEdit::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyLineEdit::staticMetaObject = {
    { &QLineEdit::staticMetaObject, qt_meta_stringdata_MyLineEdit,
      qt_meta_data_MyLineEdit, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyLineEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyLineEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyLineEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyLineEdit))
        return static_cast<void*>(const_cast< MyLineEdit*>(this));
    return QLineEdit::qt_metacast(_clname);
}

int MyLineEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLineEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MyLineEdit::setVal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyLineEdit::setValD(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
