#ifndef MERESTORE_H
#define MERESTORE_H

#include "../global.h"
#include "../unit.h"
#include "../index/index.h"
#include "../graph/graph.h"

#include <QMap>
#include <QObject>
#include <QVariant>

namespace Mere
{
namespace Store
{

namespace Type
{
    const QString STORE = "store";
    const QString SLICE = "slice";
    const QString INDEX = "index";
    const QString GRAPH = "graph";
}

class Config;

class MERE_STORE_LIBSPEC Store : public QObject
{
    Q_OBJECT
public:
    virtual ~Store();
    explicit Store(const QString &name, QObject *parent = nullptr);

    virtual Config* config() const = 0;

    virtual QString type() const;
    virtual QString store() const;

    virtual QString path() const = 0;
    virtual QString mime() const = 0;

    virtual QString home() const = 0;

//protected:
    virtual void init() = 0;
    virtual int create() = 0;
    virtual int open() = 0;
    virtual int close() = 0;
    virtual int remove() = 0;

    virtual int create(const Index &index) = 0;
    virtual int create(const Graph &graph) = 0;

signals:
    // move from here
    void saved(MereStoreUnitMap data);
    void created(MereStoreUnitMap data);
    void updated(MereStoreUnitMap data);
    void fetched(MereStoreUnitMap data);
    void removed(MereStoreUnitMap data);
    void matched(QList<MereStoreUnitMap> data);

private:
    class StorePrivate;
    StorePrivate *d_ptr;
};

} // namespace Store
} // namespace Mere

#endif // MERESTORE_H
