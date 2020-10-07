#include "ref.h"

#include "mere/utils/merestringutils.h"

bool Mere::Store::Ref::isValid() const
{
    // Unit Path
    QString path = this->path();
    if (MereStringUtils::isBlank(path))
        return false;

    // Unit Type
    QString type = this->type();
    if (MereStringUtils::isBlank(type))
        return false;

    // Unit UUID
    QUuid uuid = this->uuid();
    if (uuid.isNull())
        return false;

    return true;
};

QString Mere::Store::Ref::toString() const
{
    return QString("path:%1:type:%2:uuid:%3").arg(this->path(), this->type(), this->uuid().toString());
};
