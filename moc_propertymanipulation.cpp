/****************************************************************************
** Meta object code from reading C++ file 'propertymanipulation.h'
**
** Created: Tue Aug 14 09:45:54 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "propertymanipulation.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'propertymanipulation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Int_WGT[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,    9,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      31,    9,    8,    8, 0x0a,
      43,    9,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Int_WGT[] = {
    "Int_WGT\0\0val\0sendVal(QVariant)\0"
    "setVal(int)\0receiveVal(QVariant)\0"
};

void Int_WGT::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Int_WGT *_t = static_cast<Int_WGT *>(_o);
        switch (_id) {
        case 0: _t->sendVal((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 1: _t->setVal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->receiveVal((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Int_WGT::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Int_WGT::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Int_WGT,
      qt_meta_data_Int_WGT, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Int_WGT::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Int_WGT::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Int_WGT::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Int_WGT))
        return static_cast<void*>(const_cast< Int_WGT*>(this));
    return QWidget::qt_metacast(_clname);
}

int Int_WGT::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void Int_WGT::sendVal(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_Double_WGT[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,   12,   11,   11, 0x0a,
      46,   12,   11,   11, 0x0a,
      62,   12,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Double_WGT[] = {
    "Double_WGT\0\0val\0sendVal(QVariant)\0"
    "setVal(int)\0setValD(double)\0"
    "receiveVal(QVariant)\0"
};

void Double_WGT::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Double_WGT *_t = static_cast<Double_WGT *>(_o);
        switch (_id) {
        case 0: _t->sendVal((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 1: _t->setVal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setValD((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->receiveVal((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Double_WGT::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Double_WGT::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Double_WGT,
      qt_meta_data_Double_WGT, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Double_WGT::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Double_WGT::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Double_WGT::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Double_WGT))
        return static_cast<void*>(const_cast< Double_WGT*>(this));
    return QWidget::qt_metacast(_clname);
}

int Double_WGT::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Double_WGT::sendVal(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_Scl_WGT[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,    9,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Scl_WGT[] = {
    "Scl_WGT\0\0val\0setVal(int)\0"
};

void Scl_WGT::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Scl_WGT *_t = static_cast<Scl_WGT *>(_o);
        switch (_id) {
        case 0: _t->setVal((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Scl_WGT::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Scl_WGT::staticMetaObject = {
    { &Double_WGT::staticMetaObject, qt_meta_stringdata_Scl_WGT,
      qt_meta_data_Scl_WGT, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Scl_WGT::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Scl_WGT::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Scl_WGT::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Scl_WGT))
        return static_cast<void*>(const_cast< Scl_WGT*>(this));
    return Double_WGT::qt_metacast(_clname);
}

int Scl_WGT::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Double_WGT::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_Rot_WGT[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_Rot_WGT[] = {
    "Rot_WGT\0"
};

void Rot_WGT::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Rot_WGT::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Rot_WGT::staticMetaObject = {
    { &Double_WGT::staticMetaObject, qt_meta_stringdata_Rot_WGT,
      qt_meta_data_Rot_WGT, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Rot_WGT::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Rot_WGT::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Rot_WGT::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Rot_WGT))
        return static_cast<void*>(const_cast< Rot_WGT*>(this));
    return Double_WGT::qt_metacast(_clname);
}

int Rot_WGT::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Double_WGT::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_Binar_WGT[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,   29,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Binar_WGT[] = {
    "Binar_WGT\0\0sendVal(QVariant)\0val\0"
    "setVal(int)\0"
};

void Binar_WGT::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Binar_WGT *_t = static_cast<Binar_WGT *>(_o);
        switch (_id) {
        case 0: _t->sendVal((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 1: _t->setVal((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Binar_WGT::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Binar_WGT::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Binar_WGT,
      qt_meta_data_Binar_WGT, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Binar_WGT::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Binar_WGT::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Binar_WGT::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Binar_WGT))
        return static_cast<void*>(const_cast< Binar_WGT*>(this));
    return QWidget::qt_metacast(_clname);
}

int Binar_WGT::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Binar_WGT::sendVal(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
