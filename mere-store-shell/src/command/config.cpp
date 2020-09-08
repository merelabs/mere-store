#include "config.h"
#include "../input.h"
#include "../store.h"
#include "../app.h"

#include "mere/utils/merestringutils.h"

Config::Config(QObject *parent)
    : Config("", parent)
{

}

Config::Config(QString argument, QObject *parent)
    : Command(Command::Config, argument, parent)
{

}

bool Config::execute() const
{
    //qDebug() << "Going to run " << this->command() << " with the arguments " << this->argument();

    bool ok = false;

//    Config config;

//    QString key = this->key();
//    QString val = this->value();

//    if (MereStringUtils::isBlank(val))
//        ok = config.get(key);
//    else
//        ok = config.set(key, val);

    return ok;
}

QString Config::key() const
{
    QString key;

    int pos = this->argument().indexOf(" ");
    if(pos != -1)
        key = this->argument().left(pos);

    return key;
}

QString Config::value() const
{
    QString value;

    int pos = this->argument().indexOf(" ");
    if(pos != -1)
        value = this->argument().mid(pos + 1);

    return value;
}

