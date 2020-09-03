#include "get.h"
#include "../input.h"
#include "../store.h"
#include "../context.h"
#include "../kvutils.h"
#include "../app.h"

#include "mere/utils/merestringutils.h"

Get::Get(QObject *parent)
    : Get("", parent)
{

}

Get::Get(QString argument, QObject *parent)
    : Command(Command::Get, argument, parent)
{

}

bool Get::execute() const
{
    //qDebug() << "Going to run " << this->command() << " with the arguments " << this->argument();

    bool ok = false;

    QList<QString> keys;

    try
    {
        keys = KVUtils::blocks(this->argument());
    }
    catch (...)
    {
        qDebug() << "Exception....";
    }


    QString storeName = App::context()->get();
    Store store(storeName);

    QListIterator<QString> it(keys);
    while(it.hasNext())
    {
        QString key = it.next();
        QVariant value = store.get(key);
        qDebug() << "-" << key << value.toString();
    }

    return ok;
}

void Get::help() const
{
    qDebug() <<  "THIS IS A TEST";
}
