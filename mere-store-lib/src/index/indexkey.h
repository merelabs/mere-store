#ifndef INDEXKEY_H
#define INDEXKEY_H

#include "../key.h"
#include "../unitref.h"

namespace Mere
{
namespace Store
{

class IndexKey : public Key
{
//    Q_OBJECT
public:
    explicit IndexKey(const QString &key);

    QString what() const;
    UnitRef ref() const;
};


} // namespace Store
} // namespace Mere

#endif // INDEXKEY_H
