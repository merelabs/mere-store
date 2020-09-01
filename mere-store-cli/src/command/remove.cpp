#include "remove.h"
#include "../input.h"
#include "../store.h"

Remove::Remove(QObject *parent)
    : Remove("", parent)
{

}

Remove::Remove(QString argument, QObject *parent)
    : Command(Command::Remove, argument, parent)
{

}

bool Remove::execute() const
{
    qDebug() << "Going to run " << this->command() << " with the arguments " << this->argument();

    bool ok = false;

    if (this->object().compare("store") == 0)
    {
        Store store(this->subject());
        ok = store.remove();

        if (ok)
        {
            qDebug() << "Store " << this->subject() << " removed successfully.";
        }
        else
            qDebug() << "Store " << this->subject() << " does not exists.";
    }

    return ok;
}

QString Remove::subject() const
{
    Input input(this->argument());
    input.process();

    return input.argument();
}

QString Remove::object() const
{
    Input input(this->argument());
    input.process();

    return input.command();
}

