#ifndef MERESTOREUNITREF_H
#define MERESTOREUNITREF_H

#include "global.h"
#include "ref.h"

#include <QUuid>

namespace Mere
{
namespace Store
{

typedef QMap<QString, QVariant> UnitRefMap;

class MERE_STORE_LIBSPEC UnitRef : public Ref
{
public:
    ~UnitRef();
    explicit UnitRef();
    explicit UnitRef(const QString &ref);
    explicit UnitRef(const QMap<QString, QVariant> &map);

    QString path() const;
    void setPath(const QString &path);

    QString type() const;
    void setType(const QString type);

    QUuid uuid() const;
    void setUuid(const QUuid &uuid);

    bool isValid() const;

    UnitRefMap map() const;

private:
    class UnitRefPrivate;
    UnitRefPrivate *d_ptr;
};

} // namespace Store
} // namespace Mere

Q_DECLARE_METATYPE(Mere::Store::UnitRef);
Q_DECLARE_METATYPE(Mere::Store::UnitRef*);
Q_DECLARE_OPAQUE_POINTER(Mere::Store::UnitRef::UnitRefPrivate);
Q_DECLARE_OPAQUE_POINTER(Mere::Store::UnitRef::UnitRefPrivate*);

#endif // MERESTOREUNITREF_H
