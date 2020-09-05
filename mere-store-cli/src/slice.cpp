#include "slice.h"
#include "store.h"

#include "mere/store/format/mereunitstore.h"

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

    qDebug() << ">>>>>>" << m_store + "/slices/" + m_slice;
    MereUnitStore store(m_store, m_slice);
    s = &store;

//    QMap<QString, QVariant> map = s->get(".").toMap();
//    QMap<QString, QVariant> slices = map.value("slices").toMap();


    int ok = s->create();
    //qDebug() << " Store::create()... " << ok;

    return ok == 0;
}
