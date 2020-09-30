#ifndef UNITINDEXER_H
#define UNITINDEXER_H

#include "../store/unitstore.h"
#include "indexer.h"

#include <QObject>
#include <QDebug>

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

    int index(const QString &key, const QVariant &value) const override;

signals:
private:
    Store &m_store;
    QString m_name;
};

} // namespace Store
} // namespace Mere

#endif // UNITINDEXER_H
