#ifndef INDEXER_H
#define INDEXER_H

#include "index.h"
#include "../pair.h"
#include "../unitref.h"

#include <QObject>

namespace Mere
{
namespace Store
{

class Indexer : public QObject
{
    Q_OBJECT
public:
    explicit Indexer(QObject *parent = nullptr);

    // batch indexing
    virtual void index() const;
    virtual void index(const QString &name) const;
    virtual void index(const Index &index) const;

    // unit indexing
    virtual int index(const QString &what, const Ref &ref) const = 0;
    virtual int reindex(const QString &what, const Ref &ref) const = 0;

    // remove index
    virtual int remove(const Ref &ref) const = 0;

    // query (exact match)
    virtual UnitRef findOne(const QString &what) const = 0;
    virtual QList<UnitRef> find(const QString &what) const = 0;

    // query (partial match)
    virtual QList<Pair> query(const QString &what) const = 0;

signals:
    void indexed(const QString &name);
};

} // namespace Store
} // namespace Mere

#endif // INDEXER_H
