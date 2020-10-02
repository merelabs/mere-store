#ifndef MERESIMPLE_H
#define MERESIMPLE_H

#include "basestore.h"


namespace Mere
{
namespace Store
{

class MERE_STORE_LIBSPEC PairStore : public BaseStore
{
    Q_OBJECT
public:
    virtual ~PairStore();
    explicit PairStore(const QString &store, QObject *parent = nullptr);
    explicit PairStore(const QString &store, const QString &slice, QObject *parent = nullptr);

    virtual int set(const QVariant &value);
    virtual int set(const QString &key, const QVariant &value);
    virtual int set(const QMap<QString, QVariant> &pairs);
    virtual int set(const QList<QPair<QString, QVariant> > &pairs);

    virtual QVariant get(const QString &key);
    virtual QVariant get(const QList<QString> &keys);

    virtual int del(const QString &key);
    virtual int del(const QList<QString> &keys);

    virtual QVariant list(const int &limit = 25);
    virtual QVariant list(const QString &key, const int &limit = 25);
    virtual QVariant list(const QMap<QString, QVariant> &filter, const int &limit = 25);

private:
    class PairStorePrivate;
    PairStorePrivate *d_ptr;
};

} // namespace Store
} // namespace Mere

#endif // MERESIMPLE_H
