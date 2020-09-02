#include "del.h"
#include "../input.h"
#include "../store.h"
#include "../context.h"
#include "../kvutils.h"
#include "../merestorecli.h"

#include "mere/utils/merestringutils.h"

Del::Del(QObject *parent)
    : Del("", parent)
{

}

Del::Del(QString argument, QObject *parent)
    : Command(Command::Del, argument, parent)
{

}

bool Del::execute() const
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


    QString storeName = MereCli::context()->get();
    Store store(storeName);

    QListIterator<QString> it(keys);
    while(it.hasNext())
    {
        QString key = it.next();
        QVariant value = store.del(key);
        qDebug() << "-" << key << value.toString();
    }

    return ok;
}

void Del::help() const
{
    qDebug() <<  "THIS IS A TEST";
}
