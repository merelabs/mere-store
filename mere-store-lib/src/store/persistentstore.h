#ifndef PERSISTENTSTORE_H
#define PERSISTENTSTORE_H

#include "basestore.h"

namespace Mere
{
namespace Store
{

class Pair;
class PersistentStore : public BaseStore
{
    Q_OBJECT
public:
    virtual ~PersistentStore();
    explicit PersistentStore(const QString &store, QObject *parent = nullptr);
    explicit PersistentStore(const QString &store, const QString &slice, QObject *parent = nullptr);

    // raw - key/value pair
    /**
     * @brief set value in the store
     * @param value
     * @return
     *
     * Store the value in the store.
     * As there is no key provided, system will generate one and sore
     * the value against the key.
     *
     * System will return 0 if operation succeeded, otherwise error value.
     */
    virtual int set(const QVariant &value) = 0;

    /**
     * @brief set key/value pair in the store
     * @param key
     * @param value
     * @return
     *
     * Store the value in the store against the provided key. If there
     * is a key already defined in the store, system will ovverdide the
     * value.
     *
     * System will return 0 if operation succeeded, otherwise error value.
     */

    virtual int set(const QString &key, const QVariant &value) = 0;

    /**
     * @brief set
     * @param pairs
     * @return
     *
     * Traverse the key/value pairs and store the key/value pair
     * in the store.
     *
     * System will return 0 if operation succeeded, otherwise error value.
     */
    virtual int set(const QMap<QString, QVariant> &pairs) = 0;

    /**
     * @brief set
     * @param pairs
     * @return
     *
     * Traverse the list of pairs of key/value and store the key/value pair
     * in the store.
     *
     * System will return 0 if operation succeeded, otherwise error value.
     */
    virtual int set(const QList<Pair> &pairs) = 0;

    /**
     * @brief get
     * @param key
     * @return
     *
     * Retrieve value of a key.
     *
     */
    virtual QVariant get(const QString &key) = 0;

    /**
     * @brief get
     * @param keys
     * @return
     *
     * Retrieve values of the list of keys.
     *
     */
    virtual QVariant get(const QList<QString> &keys) = 0;

    /**
     * @brief del
     * @param key
     * @return
     *
     * Delete the entry from the store that matched with the key.
     *
     */
    virtual int del(const QString &key) = 0;

    /**
     * @brief del
     * @param keys
     * @return
     *
     * Delete entries from the store that matched with any of the key in the list.
     *
     */
    virtual int del(const QList<QString> &keys) = 0;

    /**
     * @brief del
     * @param regex
     * @return
     *
     * Delete entries from the store that matched with the regular expresion.
     *
     */
    virtual int del(const QRegExp &regex) = 0;

    /**
     * @brief list
     * @param limit
     * @return
     *
     * Retrieve a list of the entries from the store; limit defined the number of the
     * entries to be retrieved.
     *
     */
    virtual QVariant list(const int &limit = 25) = 0;

    /**
     * @brief list
     * @param key
     * @param limit
     * @return
     *
     * Retrive a list of entries startig from the "key" from the store; limit defined
     * the number of the entries to be retrieved.
     *
     */
    virtual QVariant list(const QString &key, const int &limit = 25) = 0;

    /**
     * @brief list
     * @param filter
     * @param limit
     * @return
     */
    virtual QVariant list(const QMap<QString, QVariant> &filter, const int &limit = 25) = 0;

    /**
     * @brief list
     * @param regex
     * @param limit
     * @return
     *
     * Retrive a list of entries startig from the key that matched with "regex" from the store;
     * limit defined the number of the entries to be retrieved.
     */
    virtual QVariant list(const QRegExp &regex, const int &limit) = 0;

    /**
     * @brief find
     * @param key
     * @param limit
     * @return
     *
     * Find and retrieve a list of entries that matched the "key" from the store; limit defined
     * the number of the entries to be retrieved.
     *
     */
    virtual QVariant find(const QString &key, const int &limit = 25) = 0;

private:
    class PersistentStorePrivate;
    PersistentStorePrivate *d_ptr;
};

} // namespace Store
} // namespace Mere

#endif // PERSISTENTSTORE_H
