/****************************************************************************
** Meta object code from reading C++ file 'subwindow.h'
**
** Created: Tue Aug 14 09:45:35 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "subwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'subwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SubWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      49,   10,   10,   10, 0x05,
      93,   10,   10,   10, 0x05,
     106,   10,   10,   10, 0x05,
     127,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
     166,  162,   10,   10, 0x0a,
     184,  162,   10,   10, 0x0a,
     203,  162,   10,   10, 0x0a,
     222,  162,   10,   10, 0x0a,
     241,  162,   10,   10, 0x0a,
     260,  162,   10,   10, 0x0a,
     281,  162,   10,   10, 0x0a,
     302,   10,   10,   10, 0x0a,
     326,  322,   10,   10, 0x0a,
     350,  162,   10,   10, 0x0a,
     381,  375,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SubWindow[] = {
    "SubWindow\0\0send16BitData(vector<unsigned short>)\0"
    "send16BitDataDirect(vector<unsigned short>)\0"
    "newPicture()\0DisplayModeChanged()\0"
    "fullPictureModeChanged(SubWindow*)\0"
    "val\0setLbBr(QVariant)\0setLbRot(QVariant)\0"
    "setLbCon(QVariant)\0setLbGam(QVariant)\0"
    "setLbScl(QVariant)\0setLbHFlip(QVariant)\0"
    "setLbVFlip(QVariant)\0send16BitDataSlot()\0"
    "pos\0ShowContextMenu(QPoint)\0"
    "setFullPictureMode(bool)\0event\0"
    "resizeEvent(QResizeEvent*)\0"
};

void SubWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SubWindow *_t = static_cast<SubWindow *>(_o);
        switch (_id) {
        case 0: _t->send16BitData((*reinterpret_cast< vector<unsigned short>(*)>(_a[1]))); break;
        case 1: _t->send16BitDataDirect((*reinterpret_cast< vector<unsigned short>(*)>(_a[1]))); break;
        case 2: _t->newPicture(); break;
        case 3: _t->DisplayModeChanged(); break;
        case 4: _t->fullPictureModeChanged((*reinterpret_cast< SubWindow*(*)>(_a[1]))); break;
        case 5: _t->setLbBr((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 6: _t->setLbRot((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 7: _t->setLbCon((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 8: _t->setLbGam((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 9: _t->setLbScl((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 10: _t->setLbHFlip((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 11: _t->setLbVFlip((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 12: _t->send16BitDataSlot(); break;
        case 13: _t->ShowContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 14: _t->setFullPictureMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SubWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SubWindow::staticMetaObject = {
    { &QMdiSubWindow::staticMetaObject, qt_meta_stringdata_SubWindow,
      qt_meta_data_SubWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SubWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SubWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SubWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SubWindow))
        return static_cast<void*>(const_cast< SubWindow*>(this));
    return QMdiSubWindow::qt_metacast(_clname);
}

int SubWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMdiSubWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void SubWindow::send16BitData(vector<unsigned short> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SubWindow::send16BitDataDirect(vector<unsigned short> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SubWindow::newPicture()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void SubWindow::DisplayModeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void SubWindow::fullPictureModeChanged(SubWindow * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
