/****************************************************************************
** Meta object code from reading C++ file 'slidermanip.h'
**
** Created: Tue Aug 14 09:45:53 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "slidermanip.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'slidermanip.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SliderManip[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      24,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      45,   40,   12,   12, 0x0a,
      82,   12,   12,   12, 0x0a,
     100,   12,   12,   12, 0x0a,
     118,   40,   12,   12, 0x0a,
     169,  163,   12,   12, 0x0a,
     198,  196,   12,   12, 0x0a,
     223,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SliderManip[] = {
    "SliderManip\0\0get16Bit()\0hidehistogram()\0"
    "data\0get16BitData(vector<unsigned short>)\0"
    "redrawHistogram()\0recalcHistogram()\0"
    "recalcHistogram16Bit(vector<unsigned short>)\0"
    "event\0resizeEvent(QResizeEvent*)\0e\0"
    "closeEvent(QCloseEvent*)\0turnOffHistogram()\0"
};

void SliderManip::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SliderManip *_t = static_cast<SliderManip *>(_o);
        switch (_id) {
        case 0: _t->get16Bit(); break;
        case 1: _t->hidehistogram(); break;
        case 2: _t->get16BitData((*reinterpret_cast< vector<unsigned short>(*)>(_a[1]))); break;
        case 3: _t->redrawHistogram(); break;
        case 4: _t->recalcHistogram(); break;
        case 5: _t->recalcHistogram16Bit((*reinterpret_cast< vector<unsigned short>(*)>(_a[1]))); break;
        case 6: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        case 7: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 8: _t->turnOffHistogram(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SliderManip::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SliderManip::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SliderManip,
      qt_meta_data_SliderManip, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SliderManip::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SliderManip::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SliderManip::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SliderManip))
        return static_cast<void*>(const_cast< SliderManip*>(this));
    return QWidget::qt_metacast(_clname);
}

int SliderManip::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void SliderManip::get16Bit()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void SliderManip::hidehistogram()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
