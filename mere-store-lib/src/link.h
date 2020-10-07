#ifndef LINK_H
#define LINK_H

#include "unitref.h"

#include <QString>

namespace Mere
{
namespace Store
{

class Link
{
public:
    virtual ~Link();
    Link();
    Link(const QString &name, const UnitRef &ref);
    Link(const QString &name, const QList<UnitRef> &refs);

//    bool operator==(const Link &link)
//    {
//        if (name().compare(link.name()) != 0)
//            return false;

//        return true;
//    }

    QString name() const;
    void setName(const QString &name);

    QList<UnitRef> units() const;

    void addUnit(const UnitRef &ref);
    void addUnits(const QList<UnitRef> &refs);
    void setUnits(const QList<UnitRef> &refs);

    QMap<QString, QVariant> map() const;

private:
    class LinkPrivate;
    LinkPrivate *d_ptr;
};

} // namespace Store
} // namespace Mere

#endif // LINK_H
