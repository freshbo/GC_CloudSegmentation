/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Thu 26. Feb 16:58:03 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      21,   11,   11,   11, 0x0a,
      33,   11,   11,   11, 0x0a,
      55,   11,   11,   11, 0x0a,
      72,   11,   11,   11, 0x0a,
      85,   11,   11,   11, 0x0a,
     104,   11,   11,   11, 0x0a,
     120,   11,   11,   11, 0x0a,
     129,   11,   11,   11, 0x0a,
     145,  139,   11,   11, 0x0a,
     162,   11,   11,   11, 0x0a,
     183,  139,   11,   11, 0x0a,
     208,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0loadPC()\0loadFrame()\0"
    "statisticalOutliers()\0radiusOutliers()\0"
    "downsample()\0computeCurvature()\0"
    "triangulation()\0BinSeg()\0LeafSeg()\0"
    "value\0frameScroll(int)\0updateGUIstate(bool)\0"
    "pSliderValueChanged(int)\0showCloud()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->loadPC(); break;
        case 1: _t->loadFrame(); break;
        case 2: _t->statisticalOutliers(); break;
        case 3: _t->radiusOutliers(); break;
        case 4: _t->downsample(); break;
        case 5: _t->computeCurvature(); break;
        case 6: _t->triangulation(); break;
        case 7: _t->BinSeg(); break;
        case 8: _t->LeafSeg(); break;
        case 9: _t->frameScroll((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->updateGUIstate((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->pSliderValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->showCloud(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
