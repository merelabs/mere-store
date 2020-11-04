#ifndef MERESIMPLE_H
#define MERESIMPLE_H

#include "persiststore.h"


namespace Mere
{
namespace Store
{

class Pair;
class MERE_STORE_LIBSPEC PairStore : public PersistStore
{
    Q_OBJECT
public:
    virtual ~PairStore();
    explicit PairStore(const QString &store, QObject *parent = nullptr);
    explicit PairStore(const QString &store, const QString &slice, QObject *parent = nullptr);

    virtual int set(const QVariant &value) override;
    virtual int set(const QString &key, const QVariant &value) override;
    virtual int set(const QMap<QString, QVariant> &pairs) override;
    virtual int set(const QList<Pair> &pairs) override;

    virtual QVariant get(const QString &key) override;
    virtual QVariant get(const QList<QString> &keys) override;

    virtual int del(const QString &key) override;
    virtual int del(const QList<QString> &keys) override;

    virtual int del(const QRegExp &regex) override;

    virtual QVariant list(const int &limit = 25) override;
    virtual QVariant list(const QString &key, const int &limit = 25) override;
    virtual QVariant list(const QMap<QString, QVariant> &filter, const int &limit = 25) override;

    virtual QVariant list(const QRegExp &regex, const int &limit = 0) override;

    virtual QVariant find(const QString &key, const int &limit = 25) override;

private:
    class PairStorePrivate;
    PairStorePrivate *d_ptr;
};

} // namespace Store
} // namespace Mere

#endif // MERESIMPLE_H
