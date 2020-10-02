#ifndef MEREJSONSTORE_H
#define MEREJSONSTORE_H

#include "pairstore.h"

#include <QJsonDocument>

namespace Mere
{
namespace Store
{

class MERE_STORE_LIBSPEC JsonStore : public PairStore
{
    Q_OBJECT
public:
    virtual ~JsonStore();
    explicit JsonStore(const QString &store, QObject *parent = nullptr);
    explicit JsonStore(const QString &store, const QString &slice, QObject *parent = nullptr);

    int set(const QString &key, const QVariant &value) override;

    int set(const QString &key, const QJsonArray &value);
    int set(const QString &key, const QJsonObject &value);
    int set(const QString &key, const QJsonDocument &value);

private:
    using PairStore::set;
};

} // namespace Store
} // namespace Mere

#endif // MEREJSONSTORE_H
