/****************************************************************************
** Meta object code from reading C++ file 'ludo_player_theis.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ludo/ludo_player_theis.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ludo_player_theis.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ludo_player_theis[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,
      37,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      66,   57,   18,   18, 0x0a,
     110,   97,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ludo_player_theis[] = {
    "ludo_player_theis\0\0select_piece(int)\0"
    "turn_complete(bool)\0relative\0"
    "start_turn(positions_and_dice)\0"
    "relative_pos\0post_game_analysis(std::vector<int>)\0"
};

void ludo_player_theis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ludo_player_theis *_t = static_cast<ludo_player_theis *>(_o);
        switch (_id) {
        case 0: _t->select_piece((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->turn_complete((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->start_turn((*reinterpret_cast< positions_and_dice(*)>(_a[1]))); break;
        case 3: _t->post_game_analysis((*reinterpret_cast< std::vector<int>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ludo_player_theis::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ludo_player_theis::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ludo_player_theis,
      qt_meta_data_ludo_player_theis, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ludo_player_theis::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ludo_player_theis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ludo_player_theis::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ludo_player_theis))
        return static_cast<void*>(const_cast< ludo_player_theis*>(this));
    return QObject::qt_metacast(_clname);
}

int ludo_player_theis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void ludo_player_theis::select_piece(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ludo_player_theis::turn_complete(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
