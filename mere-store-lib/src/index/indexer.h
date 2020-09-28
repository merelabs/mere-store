#ifndef INDEXER_H
#define INDEXER_H

#include "index.h"

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

    virtual void index() const;
    virtual void index(const QString &name) const;
    virtual void index(const Index &index) const;

signals:

};

} // namespace Store
} // namespace Mere

#endif // INDEXER_H
