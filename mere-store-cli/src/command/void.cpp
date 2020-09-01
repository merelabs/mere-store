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
    qDebug() << "Do nothinhg!";
    return false;
}
