#include "close.h"
#include "../input.h"

Close::Close(QObject *parent)
    : Close("", parent)
{

}

Close::Close(QString argument, QObject *parent)
    : Command(Command::Close, argument, parent)
{

}

bool Close::execute() const
{
    //qDebug() << "Going to run " << this->command() << " with the arguments " << this->argument();

    if (this->object().compare("store") == 0)
    {
//        Store store(this->subject());
//        store.create();
    }

    return false;
}

QString Close::subject() const
{
    Input input(this->argument());
    input.process();

    return input.argument();
}

QString Close::object() const
{
    Input input(this->argument());
    input.process();

    return input.command();
}

void Close::help() const
{
    qDebug() <<  "THIS IS A TEST";
}
