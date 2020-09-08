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

    virtual QVariant get(const QString &key) override;
    virtual QVariant del(const QString &key) override;

    virtual QVariant list() override;
    virtual QVariant list(const QString &key) override;

private:
    class MereSimpleStorePrivate;
    MereSimpleStorePrivate *d_ptr;
};

#endif // MERESIMPLE_H
