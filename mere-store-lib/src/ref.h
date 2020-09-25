#ifndef REF_H
#define REF_H

#include <QUuid>
#include <QString>

namespace Mere
{
namespace Store
{

class Ref
{
    virtual QString path() const = 0;
    virtual QString type() const = 0;
    virtual QUuid uuid() const   = 0;
};

} // namespace Store
} // namespace Mere

#endif // REF_H
