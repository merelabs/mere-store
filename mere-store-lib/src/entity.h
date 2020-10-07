#ifndef ENTRY_H
#define ENTRY_H

#include "pair.h"
#include "unit.h"
#include "unitref.h"

namespace Mere
{
namespace Store
{

class Entity
{
public:
    ~Entity();

    explicit Entity();
    explicit Entity(const Ref &ref);

    //Entity(const Entity &other) = default;

    UnitRef ref() const;
    void set(const Ref &ref);

    int set(const Pair &pair);
    int set(const QList<Pair> &pairs);

    int add(const Pair &pair);
    int add(const QList<Pair> &pairs);

    int del(const Pair &pair);
    int del(const QList<Pair> &pairs);

    QList<Pair> pairs() const;

    int add(const QString &key, const QVariant &value);
    int set(const QMap<QString, QVariant> &entries);

    QMap<QString, QVariant> map() const;

private:
    class EntityPrivate;
    EntityPrivate *d_ptr;
};

} // namespace Store
} // namespace Mere

Q_DECLARE_METATYPE(Mere::Store::Entity);
Q_DECLARE_METATYPE(Mere::Store::Entity*);

#endif // ENTRY_H
