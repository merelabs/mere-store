#ifndef HEXASTORE_H
#define HEXASTORE_H

#include "groupstore.h"

namespace Mere
{
namespace Store
{

class HexaStore : public GroupStore
{
    Q_OBJECT
public:
    virtual ~HexaStore();
    explicit HexaStore(const QString &store, QObject *parent = nullptr);
    explicit HexaStore(const QString &store, const QString &slice, QObject *parent = nullptr);

    enum Flow {InComing, OutGoing};

//    void add(const UnitRef &subject, const QString &predicate, const UnitRef &object);
    virtual int add(const QString &subject, const QString &predicate, const QString &object) const;
    virtual int del(const QString &subject, const QString &predicate, const QString &object) const;

    //
    // Queries
    //

    // All the vertex that going from or coming to
    //virtual QList<UnitRef> vertex(const UnitRef &ref, HexaStore::Flow flow = InComing) const;
    virtual QList<QString> vertex(const QString &vertex, HexaStore::Flow flow = InComing) const;

    // All the vertex that going from or coming to via arc
    //virtual QList<UnitRef> vertex(const UnitRef &ref, const QString &predicate, HexaStore::Flow flow = InComing) const;
    virtual QList<QString> vertex(const QString &vertex, const QString &predicate, HexaStore::Flow flow = InComing) const;

    // All the vertex connected by predcate
    //virtual QList<UnitRef> vertex(const QString &predicate) const;
    virtual QList<QString> vertex(const QString &predicate) const;

    virtual QList<QString> arc(const QString &subject, const QString &object) const;

    // avoid warning
    using PairStore::del;

private:
    static QString HEXA_KEY_1, HEXA_KEY_2, HEXA_KEY_3, HEXA_KEY_4, HEXA_KEY_5, HEXA_KEY_6;

    class HexaStorePrivate;
    HexaStorePrivate *d_ptr;
};

} // namespace Store
} // namespace Mere

#endif // HEXASTORE_H
