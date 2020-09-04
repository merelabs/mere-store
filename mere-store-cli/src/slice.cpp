#include "slice.h"
#include "store.h"

#include "mere/store/format/meredefaultstore.h"

Slice::Slice(QObject *parent)
    : Slice("", "", parent)
{

}

Slice::Slice(const QString &store, const QString &slice, QObject *parent)
    : QObject(parent),
      m_store(store),
      m_slice(slice)
{

}

bool Slice::create() const
{
    MereStore *s;

    MereDefaultStore store(m_store);
    s = &store;

//    QMap<QString, QVariant> map = s->get(".").toMap();
//    QMap<QString, QVariant> slices = map.value("slices").toMap();


    int ok = s->create();
    //qDebug() << " Store::create()... " << ok;

    return ok == 0;
}
