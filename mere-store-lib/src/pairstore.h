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

    virtual int set(QVariant value) override;
    virtual int set(const QString key, QVariant value) override;
    virtual int set(const QList<QPair<QString, QVariant> > &pairs) override;

    virtual QVariant get(const QString &key) override;

    virtual int del(const QString &key) override;
    virtual int del(const QList<QString> &keys) override;

    virtual QVariant list(const uint &limit = 25) override;
    virtual QVariant list(const QString &key, const uint &limit = 25) override;
    virtual QVariant list(const QMap<QString, QVariant> &filter, const uint &limit = 25) override;

private:
    class PairStorePrivate;
    PairStorePrivate *d_ptr;
};

} // namespace Store
} // namespace Mere

#endif // MERESIMPLE_H
