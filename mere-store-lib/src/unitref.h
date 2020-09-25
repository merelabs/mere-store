#ifndef MERESTOREUNITREF_H
#define MERESTOREUNITREF_H

#include "merestoreglobal.h"
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

    QString type() const;
    void setType(const QString type);

    QUuid uuid() const;
    void setUuid(const QUuid &uuid);

    QString path() const;
    void setPath(const QString &path);

    UnitRefMap map() const;

private:
    class UnitRefPrivate;
    UnitRefPrivate *d_ptr;
};

} // namespace Store
} // namespace Mere

#endif // MERESTOREUNITREF_H
