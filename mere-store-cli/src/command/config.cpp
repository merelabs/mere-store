#include "config.h"
#include "../input.h"
#include "../store.h"

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
    qDebug() << "Going to run " << this->command() << " with the arguments " << this->argument();

    bool ok = false;

    if (this->object().compare("store") == 0)
    {
//        Store store(this->subject());
//        ok = store.create();

//        if (ok)
//        {
//            qDebug() << "Store " << this->subject() << " created successfully.";
//            store.close();
//        }
//        else
//            qDebug() << "Store " << this->subject() << " already exists.";
    }

    return ok;
}

QString Config::subject() const
{
    Input input(this->argument());
    input.process();

    return input.argument();
}

QString Config::object() const
{
    Input input(this->argument());
    input.process();

    return input.command();
}
