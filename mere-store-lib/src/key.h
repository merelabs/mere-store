#ifndef KEY_H
#define KEY_H

#include <QString>

namespace Mere
{
namespace Store
{

class Key : public QString
{
public:
    Key(const QString &key);
};

} // namespace Store
} // namespace Mere

#endif // KEY_H
