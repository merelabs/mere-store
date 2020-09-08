#include "void.h"

Void::Void(QObject *parent)
    : Void("", parent)
{

}

Void::Void(QString argument, QObject *parent)
    : Command(Command::Void, argument, parent)
{

}


bool Void::execute() const
{
    qDebug() << "Invalid command to process. Please run help command to get help.";
    return false;
}

void Void::help() const
{
    qDebug() <<  "...";
}
