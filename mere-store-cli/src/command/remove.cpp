#include "remove.h"
#include "../store.h"
#include "../kvutils.h"

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
    //qDebug() << "Going to run " << this->command() << " with the arguments " << this->argument();

    bool ok = false;

    QList<QString> blocks;

    try
    {
        blocks = KVUtils::blocks(this->argument());
    }
    catch (...)
    {
        qDebug() << "Exception....";
    }

    QString object = blocks.at(0);
    if (object.compare("store") == 0)
        ok = removeStore(blocks.at(1));
    else if (object.compare("store") == 0)
        ok = removeSlice(blocks.at(1));

    return ok;
}

bool Remove::removeStore(const QString &store) const
{
    bool ok = false;

    Store s(store);
    ok = s.remove();

    if (ok)
    {
        qDebug() << "Store " << store << " removed successfully.";
        s.close();
    }
    else
        qDebug() << "Store " << store << " does not exists.";

    return ok;
}

bool Remove::removeSlice(const QString &slice) const
{
    return false;
}

void Remove::help() const
{
    qDebug() <<  "THIS IS A TEST";
}

