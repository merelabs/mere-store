#include "ref.h"

#include "mere/utils/stringutils.h"

bool Mere::Store::Ref::isValid() const
{
    // Unit UUID
    QString id = this->id();
    if (Mere::Utils::StringUtils::isBlank(id))
        return false;

    // Unit Type
    QString type = this->type();
    if (Mere::Utils::StringUtils::isBlank(type))
        return false;

    // Unit Path
    QString path = this->path();
    if (Mere::Utils::StringUtils::isBlank(path))
        return false;

    return true;
};

QString Mere::Store::Ref::key() const
{
    return QString("p:%1:t:%2:i:%3").arg(this->path(), this->type(), this->id());
};

QMap<QString, QVariant> Mere::Store::Ref::map() const
{
    QMap<QString, QVariant> ref;

    ref.insert("id", id());
    ref.insert("type", type());
    ref.insert("path", path());

    return ref;
}
