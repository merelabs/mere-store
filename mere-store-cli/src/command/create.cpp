#include "create.h"
#include "../input.h"
#include "../store.h"

Create::Create(QObject *parent)
    : Create("", parent)
{

}

Create::Create(QString argument, QObject *parent)
    : Command(Command::Create, argument, parent)
{

}

bool Create::execute() const
{
    qDebug() << "Going to run " << this->command() << " with the arguments " << this->argument();

    bool ok = false;

    if (this->object().compare("store") == 0)
    {
        Store store(this->subject());
        ok = store.create();

        if (ok)
        {
            qDebug() << "Store " << this->subject() << " created successfully.";
            store.close();
        }
        else
            qDebug() << "Store " << this->subject() << " already exists.";
    }

    return ok;
}

QString Create::subject() const
{
    Input input(this->argument());
    input.process();

    return input.argument();
}

QString Create::object() const
{
    Input input(this->argument());
    input.process();

    return input.command();
}
