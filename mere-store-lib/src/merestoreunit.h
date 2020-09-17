#ifndef MERESTOREUNIT_H
#define MERESTOREUNIT_H

#include "merestoreglobal.h"
#include "merestoreunitref.h"
//#include "merestoreunitdescriptor.h"

#include <QMap>
#include <QVariant>

typedef QMap<QString, QVariant> MereStoreUnitMap;
typedef QMap<QString, QVariant> MereStoreUnitAttributes;
typedef QMap<QString, QList<MereStoreUnitRef>> MereStoreUnitLinks;

class MERE_STORE_LIBSPEC MereStoreUnit : public MereStoreUnitRef
{
public:
    virtual ~MereStoreUnit();
    explicit MereStoreUnit(const QString &type);

    MereStoreUnit() = default;
    MereStoreUnit(const MereStoreUnit &other) = default;

    virtual MereStoreUnitAttributes attributes() const;
    virtual void setAttributes(MereStoreUnitAttributes attributes);

    virtual void addAttribute(const QString &name, const QVariant &value);
    virtual void addAttributes(MereStoreUnitAttributes attributes);

    virtual MereStoreUnitLinks links() const;
    virtual void setLink(const QString &link, const MereStoreUnitRef &ref);
    virtual void setLinks(const QString &link, const QList<MereStoreUnitRef> &refs);

    virtual void addLink(const QString &link, const MereStoreUnitRef &ref);
    virtual void addLinks(const QString &link, const QList<MereStoreUnitRef> &refs);

    MereStoreUnitMap map() const;

private:
    class MereStoreUnitPrivate;
    MereStoreUnitPrivate *d_ptr;
};

Q_DECLARE_METATYPE(MereStoreUnit);
Q_DECLARE_METATYPE(MereStoreUnit*);
Q_DECLARE_OPAQUE_POINTER(MereStoreUnit::MereStoreUnitPrivate);
Q_DECLARE_OPAQUE_POINTER(MereStoreUnit::MereStoreUnitPrivate*);

#endif // MERESTOREUNIT_H
