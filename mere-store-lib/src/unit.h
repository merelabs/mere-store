#ifndef MERESTOREUNIT_H
#define MERESTOREUNIT_H

#include "global.h"
#include "unitref.h"
#include "link.h"
//#include "merestoreunitdescriptor.h"

#include <QMap>
#include <QVariant>

namespace Mere
{
namespace Store
{

typedef QMap<QString, QVariant> MereStoreUnitMap;
typedef QMap<QString, QVariant> MereStoreUnitAttributes;
typedef QList<Link> MereStoreUnitLinks;

class MERE_STORE_LIBSPEC Unit : public UnitRef
{
public:
    virtual ~Unit();
    Unit();
    Unit(const QString &type);
    Unit(const QMap<QString, QVariant> &map);

    Unit(const Unit &other) = default;

    virtual MereStoreUnitAttributes attributes() const;
    virtual void setAttributes(MereStoreUnitAttributes attributes);

    virtual void addAttribute(const QString &name, const QVariant &value);
    virtual void addAttributes(MereStoreUnitAttributes attributes);

    virtual MereStoreUnitLinks links() const;

    virtual void setLink(const QString &name, const UnitRef &ref);
    virtual void setLinks(const QString &name, const QList<UnitRef> &refs);

    virtual void setLink(const Link &name);
    virtual void setLinks(const QList<Link> &links);

    virtual void addLink(const QString &name, const UnitRef &ref);
    virtual void addLinks(const QString &link, const QList<UnitRef> &refs);

    MereStoreUnitMap map() const;

private:
    class UnitPrivate;
    UnitPrivate *d_ptr;
};

} // namespace Store
} // namespace Mere

Q_DECLARE_METATYPE(Mere::Store::Unit);
Q_DECLARE_METATYPE(Mere::Store::Unit*);
Q_DECLARE_OPAQUE_POINTER(Mere::Store::Unit::UnitPrivate);
Q_DECLARE_OPAQUE_POINTER(Mere::Store::Unit::UnitPrivate*);

#endif // MERESTOREUNIT_H
