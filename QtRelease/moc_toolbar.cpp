/****************************************************************************
** Meta object code from reading C++ file 'toolbar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Course_work/toolbar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'toolbar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ToolBar_t {
    QByteArrayData data[22];
    char stringdata0[260];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ToolBar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ToolBar_t qt_meta_stringdata_ToolBar = {
    {
QT_MOC_LITERAL(0, 0, 7), // "ToolBar"
QT_MOC_LITERAL(1, 8, 10), // "changeFont"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 10), // "toggleBold"
QT_MOC_LITERAL(4, 31, 12), // "toggleItalic"
QT_MOC_LITERAL(5, 44, 15), // "toggleUnderline"
QT_MOC_LITERAL(6, 60, 11), // "changeColor"
QT_MOC_LITERAL(7, 72, 13), // "changeBgColor"
QT_MOC_LITERAL(8, 86, 14), // "changeFontSize"
QT_MOC_LITERAL(9, 101, 4), // "size"
QT_MOC_LITERAL(10, 106, 9), // "alignLeft"
QT_MOC_LITERAL(11, 116, 11), // "alignCenter"
QT_MOC_LITERAL(12, 128, 10), // "alignRight"
QT_MOC_LITERAL(13, 139, 12), // "alignJustify"
QT_MOC_LITERAL(14, 152, 15), // "clearFormatting"
QT_MOC_LITERAL(15, 168, 16), // "insertBulletList"
QT_MOC_LITERAL(16, 185, 18), // "insertNumberedList"
QT_MOC_LITERAL(17, 204, 14), // "setLineSpacing"
QT_MOC_LITERAL(18, 219, 7), // "spacing"
QT_MOC_LITERAL(19, 227, 13), // "setTextIndent"
QT_MOC_LITERAL(20, 241, 6), // "indent"
QT_MOC_LITERAL(21, 248, 11) // "insertTable"

    },
    "ToolBar\0changeFont\0\0toggleBold\0"
    "toggleItalic\0toggleUnderline\0changeColor\0"
    "changeBgColor\0changeFontSize\0size\0"
    "alignLeft\0alignCenter\0alignRight\0"
    "alignJustify\0clearFormatting\0"
    "insertBulletList\0insertNumberedList\0"
    "setLineSpacing\0spacing\0setTextIndent\0"
    "indent\0insertTable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ToolBar[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x08 /* Private */,
       3,    0,  100,    2, 0x08 /* Private */,
       4,    0,  101,    2, 0x08 /* Private */,
       5,    0,  102,    2, 0x08 /* Private */,
       6,    0,  103,    2, 0x08 /* Private */,
       7,    0,  104,    2, 0x08 /* Private */,
       8,    1,  105,    2, 0x08 /* Private */,
      10,    0,  108,    2, 0x08 /* Private */,
      11,    0,  109,    2, 0x08 /* Private */,
      12,    0,  110,    2, 0x08 /* Private */,
      13,    0,  111,    2, 0x08 /* Private */,
      14,    0,  112,    2, 0x08 /* Private */,
      15,    0,  113,    2, 0x08 /* Private */,
      16,    0,  114,    2, 0x08 /* Private */,
      17,    1,  115,    2, 0x08 /* Private */,
      19,    1,  118,    2, 0x08 /* Private */,
      21,    0,  121,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   18,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void,

       0        // eod
};

void ToolBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ToolBar *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->changeFont(); break;
        case 1: _t->toggleBold(); break;
        case 2: _t->toggleItalic(); break;
        case 3: _t->toggleUnderline(); break;
        case 4: _t->changeColor(); break;
        case 5: _t->changeBgColor(); break;
        case 6: _t->changeFontSize((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->alignLeft(); break;
        case 8: _t->alignCenter(); break;
        case 9: _t->alignRight(); break;
        case 10: _t->alignJustify(); break;
        case 11: _t->clearFormatting(); break;
        case 12: _t->insertBulletList(); break;
        case 13: _t->insertNumberedList(); break;
        case 14: _t->setLineSpacing((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->setTextIndent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->insertTable(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ToolBar::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ToolBar.data,
    qt_meta_data_ToolBar,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ToolBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ToolBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ToolBar.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ToolBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
