#include "set.h"
#include "../store.h"
#include "../slice.h"
#include "../context.h"
#include "../shell.h"

#include "mere/utils/merestringutils.h"

Set::Set(QObject *parent)
    : Set("", parent)
{

}

Set::Set(QString argument, QObject *parent)
    : Command(Command::Set, argument, parent)
{

}

bool Set::execute() const
{
    //qDebug() << "Going to run " << this->command() << " with the arguments " << this->argument();

    bool ok = false;

    QString key = this->key();
    QString val = this->value();

    ok = set(key, val);

    return ok;
}

QString Set::key() const
{
    QString key;

    int pos = this->argument().indexOf(" ");
    if(pos != -1)
        key = this->argument().left(pos);

    return key;
}

QString Set::value() const
{
    QString value;

    int pos = this->argument().indexOf(" ");
    if(pos != -1)
        value = this->argument().mid(pos + 1);

    return value;
}

bool Set::set(const QString &key, const QString &value) const
{
    bool ok = false;

    if (MereStringUtils::isBlank(Shell::context()->slice()))
        ok = setStore(key, value);
    else
        ok = setSlice(key, value);

    return ok;
}

bool Set::setStore(const QString &key, const QString &val) const
{
    bool ok = false;

    QString storeName = Shell::context()->store();
    Store store(storeName);

    if (MereStringUtils::isBlank(val))
        ok = store.set(key);
    else
        ok = store.set(key, val);

    return ok;
}

bool Set::setSlice(const QString &key, const QString &val) const
{
    bool ok = false;

    QString storeName = Shell::context()->store();
    QString sliceName = Shell::context()->slice();
    Slice slice(storeName, sliceName);

    if (MereStringUtils::isBlank(val))
        ok = slice.set(key);
    else
        ok = slice.set(key, val);

    return ok;
}
