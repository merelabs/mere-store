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
