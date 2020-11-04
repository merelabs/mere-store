#ifndef UNITINDEXER_H
#define UNITINDEXER_H

#include "../store/unitstore.h"
#include "indexer.h"

namespace Mere
{
namespace Store
{

class UnitIndexer : public Indexer
{
    Q_OBJECT
public:
    virtual ~UnitIndexer();
    UnitIndexer(Store &store, const QString &name, QObject *parent = nullptr);

    int index(const QString &key, const Ref &ref) const override;
    int reindex(const QString &key, const Ref &ref) const override;
    int remove(const Ref &ref) const override;

    UnitRef findOne(const QString &what) const override;
    QList<UnitRef> find(const QString &what) const override;
    QList<Pair> query(const QString &what) const override;

signals:
private:
    Store &m_store;
    QString m_name;
};

} // namespace Store
} // namespace Mere

#endif // UNITINDEXER_H
