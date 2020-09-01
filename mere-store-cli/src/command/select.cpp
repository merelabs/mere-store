#include "select.h"
#include "../input.h"
#include "../store.h"
#include "../context.h"

#include "../merestorecli.h"

Select::Select(QObject *parent)
    : Select("", parent)
{

}

Select::Select(QString argument, QObject *parent)
    : Command(Command::Select, argument, parent)
{
    connect(this, SIGNAL(selected(QString)), MereCli::context(), SLOT(selected(QString)));
}

bool Select::execute() const
{
    qDebug() << "Going to run " << this->command() << " with the arguments " << this->argument();

    bool ok = false;

    if (this->object().compare("store") == 0)
    {
        Store store(this->subject());
        ok = store.select();

        if (ok)
        {
            qDebug() << "Store " << this->subject() << " selected successfully.";
            emit selected(this->subject());
        }
        else
            qDebug() << "Store " << this->subject() << " does not exists.";
    }

    return ok;
}

QString Select::subject() const
{
    Input input(this->argument());
    input.process();

    return input.argument();
}

QString Select::object() const
{
    Input input(this->argument());
    input.process();

    return input.command();
}
