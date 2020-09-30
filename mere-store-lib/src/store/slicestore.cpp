#include "slicestore.h"

Mere::Store::SliceStore::SliceStore(const Store &store, const QString &name, QObject *parent)
    : UnitStore(store.home() + "/slices/"+ name, parent)
{

}
