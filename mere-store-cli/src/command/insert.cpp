#include "insert.h"
#include "../input.h"
#include "../store.h"

Insert::Insert(QObject *parent)
    : Insert("", parent)
{

}

Insert::Insert(QString argument, QObject *parent)
    : Command(Command::Insert, argument, parent)
{

}

bool Insert::execute() const
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

QString Insert::subject() const
{
    Input input(this->argument());
    input.process();

    return input.argument();
}

QString Insert::object() const
{
    Input input(this->argument());
    input.process();

    return input.command();
}
