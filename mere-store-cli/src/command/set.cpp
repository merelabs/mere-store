#include "set.h"
#include "../store.h"
#include "../context.h"
#include "../app.h"

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

    QString storeName = App::context()->store();
    Store store(storeName);

    QString key = this->key();
    QString val = this->value();

    if (MereStringUtils::isBlank(val))
        ok = store.set(key);
    else
        ok = store.set(key, val);

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

