#ifndef MERESTOREUNITREF_H
#define MERESTOREUNITREF_H

#include "global.h"
#include "ref.h"

#include <QVariant>

namespace Mere
{
namespace Store
{

typedef QMap<QString, QVariant> UnitRefMap;

class MERE_STORE_LIBSPEC UnitRef : public Ref
{
public:
    virtual ~UnitRef();
    explicit UnitRef();
    explicit UnitRef(const QString &ref);
    explicit UnitRef(const QMap<QString, QVariant> &map);

    bool operator==(const UnitRef &ref)
    {
        if (id().compare(ref.id()) != 0)
            return false;

        if (type().compare(ref.type()) != 0)
            return false;

        if (path().compare(ref.path()) != 0)
            return false;

        return true;
    }

    QString path() const;
    void setPath(const QString &path);

    QString type() const;
    void setType(const QString type);

    QString id() const;
    void setId(const QString &id);

private:
    class UnitRefPrivate;
    UnitRefPrivate *d_ptr;
};

} // namespace Store
} // namespace Mere

Q_DECLARE_METATYPE(Mere::Store::UnitRef);
Q_DECLARE_METATYPE(Mere::Store::UnitRef*);
//Q_DECLARE_OPAQUE_POINTER(Mere::Store::UnitRef::UnitRefPrivate);
//Q_DECLARE_OPAQUE_POINTER(Mere::Store::UnitRef::UnitRefPrivate*);

#endif // MERESTOREUNITREF_H
