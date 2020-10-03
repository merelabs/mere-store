#ifndef INDEXER_H
#define INDEXER_H

#include "index.h"

#include <QObject>
#include <QDebug>

namespace Mere
{
namespace Store
{

class Indexer : public QObject
{
    Q_OBJECT
public:
    explicit Indexer(QObject *parent = nullptr);

    virtual void index() const;
    virtual void index(const QString &name) const;
    virtual void index(const Index &index) const;

    virtual int index(const QString &key, const QVariant &value) const = 0;
    virtual QMap<QString, QVariant> find(const QString &what) const = 0;

signals:

};

} // namespace Store
} // namespace Mere

#endif // INDEXER_H
