#ifndef MERESIMPLE_H
#define MERESIMPLE_H

#include "../merestoreglobal.h"
#include "../merebasestore.h"
#include "../merestoreunit.h"


#include <QObject>

class MereSimpleStore : public MereBaseStore
{
    Q_OBJECT
public:
    virtual ~MereSimpleStore();
    explicit MereSimpleStore(const QString store, QObject *parent = nullptr);

    virtual int set(QVariant value) override;
    virtual int set(const QString key, QVariant value) override;

    virtual QVariant get(const QString &key) override;
    virtual QVariant del(const QString &key) override;

    virtual QVariant list() override;

signals:

private:
    class MereSimpleStorePrivate;
    MereSimpleStorePrivate *d_ptr;
};

#endif // MERESIMPLE_H
