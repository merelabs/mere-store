#ifndef PERSISTENTSTORE_H
#define PERSISTENTSTORE_H

#include "basestore.h"

namespace Mere
{
namespace Store
{

class PersistentStore : public BaseStore
{
    Q_OBJECT
public:
    virtual ~PersistentStore();
    explicit PersistentStore(const QString &store, QObject *parent = nullptr);
    explicit PersistentStore(const QString &store, const QString &slice, QObject *parent = nullptr);

    // raw - key/value pair
    virtual int set(QVariant value) = 0;
    virtual int set(const QString key, QVariant value) = 0;
    virtual int set(const QMap<QString, QVariant> &pairs) = 0;
    virtual int set(const QList<QPair<QString, QVariant>> &pairs) = 0;

    virtual QVariant get(const QString &key) = 0;
    virtual QVariant get(const QList<QString> &keys) = 0;

    virtual int del(const QString &key) = 0;
    virtual int del(const QList<QString> &keys) = 0;

    virtual QVariant list(const int &limit = 25) = 0;
    virtual QVariant list(const QString &key, const int &limit = 25) = 0;
    virtual QVariant list(const QMap<QString, QVariant> &filter, const int &limit = 25) = 0;

private:
    class PersistentStorePrivate;
    PersistentStorePrivate *d_ptr;
};

} // namespace Store
} // namespace Mere

#endif // PERSISTENTSTORE_H
