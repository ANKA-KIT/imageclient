/****************************************************************************
** Meta object code from reading C++ file 'imagewidget.h'
**
** Created: Tue Aug 14 09:45:41 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "imagewidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imagewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImageWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   13,   12,   12, 0x05,
      39,   12,   12,   12, 0x05,
      56,   52,   12,   12, 0x05,
      87,   79,   12,   12, 0x05,
     117,  113,   12,   12, 0x05,
     145,  139,   12,   12, 0x05,
     179,  175,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     199,   12,   12,   12, 0x0a,
     209,   12,   12,   12, 0x0a,
     220,   12,   12,   12, 0x0a,
     238,   12,   12,   12, 0x0a,
     254,  249,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ImageWidget[] = {
    "ImageWidget\0\0X,Y\0resizeImgWgt(int,int)\0"
    "repainting()\0x,y\0mousePosition(int,int)\0"
    "RGB,val\0mousePositionVal(int,int)\0RGB\0"
    "mousePositionVal(int)\0R,G,B\0"
    "mousePositionVal(int,int,int)\0val\0"
    "sendScale(QVariant)\0saveImg()\0printImg()\0"
    "setAllValues(int)\0rescreen()\0type\0"
    "setImgType(int)\0"
};

void ImageWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ImageWidget *_t = static_cast<ImageWidget *>(_o);
        switch (_id) {
        case 0: _t->resizeImgWgt((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->repainting(); break;
        case 2: _t->mousePosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->mousePositionVal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->mousePositionVal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->mousePositionVal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: _t->sendScale((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 7: _t->saveImg(); break;
        case 8: _t->printImg(); break;
        case 9: _t->setAllValues((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->rescreen(); break;
        case 11: _t->setImgType((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ImageWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ImageWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ImageWidget,
      qt_meta_data_ImageWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ImageWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ImageWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ImageWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImageWidget))
        return static_cast<void*>(const_cast< ImageWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ImageWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void ImageWidget::resizeImgWgt(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ImageWidget::repainting()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ImageWidget::mousePosition(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ImageWidget::mousePositionVal(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ImageWidget::mousePositionVal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ImageWidget::mousePositionVal(int _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ImageWidget::sendScale(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
