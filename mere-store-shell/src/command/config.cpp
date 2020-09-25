#include "config.h"
#include "../input.h"
#include "../store.h"
#include "../shell.h"
#include "../konfig.h"

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

    QString key = this->key();
    QString value = this->value();

    Konfig config;

    if (MereStringUtils::isBlank(value))
    {
        value = config.get(key);
        ok = true;

        QTextStream(stdout) << "Current store " << key << " : " << value << Qt::endl;
    }
    else
    {
        ok = config.set(key, value);
        QTextStream(stdout) << "Store " << key << " set to : " << value << Qt::endl;
    }

    return ok;
}

QString Config::key() const
{
    QString key;

    int pos = this->argument().indexOf(" ");
    if(pos != -1)
    {
        key = this->argument().left(pos);
    }
    else
    {
        key = this->argument();
    }

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

