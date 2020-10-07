#ifndef REF_H
#define REF_H

#include <QUuid>
#include <QString>
#include <QVariant>

namespace Mere
{
namespace Store
{

class Ref
{
public:
    virtual QString path() const = 0;
    virtual QString type() const = 0;
    virtual QUuid uuid() const   = 0;

    virtual bool isValid() const;

    virtual QString toString() const;
    virtual QMap<QString, QVariant> map() const = 0;
};

} // namespace Store
} // namespace Mere

#endif // REF_H
