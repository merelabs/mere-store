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
    //qDebug() << "Going to run " << this->command() << " with the arguments " << this->argument();

    bool ok = false;


    return ok;
}
