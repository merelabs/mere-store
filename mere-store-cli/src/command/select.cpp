#include "select.h"
#include "../store.h"
#include "../context.h"
#include "../kvutils.h"
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
        ok = selectStore(blocks.at(1));
    else if (object.compare("store") == 0)
        ok = selectSlice(blocks.at(1));


    return ok;
}

bool Select::selectStore(const QString &store) const
{
    bool ok = false;

    Store s(store);
    ok = s.select();

    if (ok)
    {
        qDebug() << "Store " << store << " selected successfully.";
        s.close();
        emit selected(store);
    }
    else
        qDebug() << "Store " << store << " does not exists.";

    return ok;
}

bool Select::selectSlice(const QString &slice) const
{
    return false;
}

void Select::help() const
{
    qDebug() <<  "THIS IS A TEST";
}

