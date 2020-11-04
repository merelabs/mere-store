#ifndef MERE_STORE_REF_H
#define MERE_STORE_REF_H

#include <QString>
#include <QVariant>

namespace Mere
{
namespace Store
{

class Ref
{
public:
    virtual QString id() const   = 0;
    virtual QString type() const = 0;
    virtual QString path() const = 0;

    virtual bool isValid() const final;
    virtual QString key() const final;
    virtual QMap<QString, QVariant> map() const;
};

} // namespace Store
} // namespace Mere

#endif // MERE_STORE_REF_H
