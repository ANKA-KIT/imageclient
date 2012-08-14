/****************************************************************************
** Meta object code from reading C++ file 'bgcpl_wgt.h'
**
** Created: Tue Aug 14 09:45:52 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "bgcpl_wgt.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bgcpl_wgt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_br_gm_con_pixLevel__BGCPL_WGT[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      31,   30,   30,   30, 0x05,
      58,   30,   30,   30, 0x05,
      85,   30,   30,   30, 0x05,
     101,   30,   30,   30, 0x05,
     118,   30,   30,   30, 0x05,

 // slots: signature, parameters, type, tag, flags
     134,   30,   30,   30, 0x0a,
     153,   30,   30,   30, 0x0a,
     177,  173,   30,   30, 0x0a,
     191,  173,   30,   30, 0x0a,
     206,  173,   30,   30, 0x0a,
     220,  173,   30,   30, 0x0a,
     240,  173,   30,   30, 0x0a,
     261,  173,   30,   30, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_br_gm_con_pixLevel__BGCPL_WGT[] = {
    "br_gm_con_pixLevel::BGCPL_WGT\0\0"
    "setRBorder(unsigned short)\0"
    "setLBorder(unsigned short)\0setBr(QVariant)\0"
    "setCon(QVariant)\0setGm(QVariant)\0"
    "setLeftBorder(int)\0setRightBorder(int)\0"
    "val\0setBrImg(int)\0setConImg(int)\0"
    "setGmImg(int)\0receiveBr(QVariant)\0"
    "receiveCon(QVariant)\0receiveGm(QVariant)\0"
};

void br_gm_con_pixLevel::BGCPL_WGT::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BGCPL_WGT *_t = static_cast<BGCPL_WGT *>(_o);
        switch (_id) {
        case 0: _t->setRBorder((*reinterpret_cast< unsigned short(*)>(_a[1]))); break;
        case 1: _t->setLBorder((*reinterpret_cast< unsigned short(*)>(_a[1]))); break;
        case 2: _t->setBr((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 3: _t->setCon((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 4: _t->setGm((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 5: _t->setLeftBorder((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setRightBorder((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->setBrImg((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->setConImg((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->setGmImg((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->receiveBr((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 11: _t->receiveCon((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 12: _t->receiveGm((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData br_gm_con_pixLevel::BGCPL_WGT::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject br_gm_con_pixLevel::BGCPL_WGT::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_br_gm_con_pixLevel__BGCPL_WGT,
      qt_meta_data_br_gm_con_pixLevel__BGCPL_WGT, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &br_gm_con_pixLevel::BGCPL_WGT::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *br_gm_con_pixLevel::BGCPL_WGT::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *br_gm_con_pixLevel::BGCPL_WGT::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_br_gm_con_pixLevel__BGCPL_WGT))
        return static_cast<void*>(const_cast< BGCPL_WGT*>(this));
    return QWidget::qt_metacast(_clname);
}

int br_gm_con_pixLevel::BGCPL_WGT::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void br_gm_con_pixLevel::BGCPL_WGT::setRBorder(unsigned short _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void br_gm_con_pixLevel::BGCPL_WGT::setLBorder(unsigned short _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void br_gm_con_pixLevel::BGCPL_WGT::setBr(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void br_gm_con_pixLevel::BGCPL_WGT::setCon(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void br_gm_con_pixLevel::BGCPL_WGT::setGm(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
