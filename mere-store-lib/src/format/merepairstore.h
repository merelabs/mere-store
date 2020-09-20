#ifndef MERESIMPLE_H
#define MERESIMPLE_H

#include "../merebasestore.h"

class MERE_STORE_LIBSPEC MerePairStore : public MereBaseStore
{
    Q_OBJECT
public:
    virtual ~MerePairStore();
    explicit MerePairStore(const QString &store, QObject *parent = nullptr);
    explicit MerePairStore(const QString &store, const QString &slice, QObject *parent = nullptr);

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
    class MerePairStorePrivate;
    MerePairStorePrivate *d_ptr;
};

#endif // MERESIMPLE_H
