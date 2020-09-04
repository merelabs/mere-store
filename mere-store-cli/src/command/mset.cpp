#include "mset.h"
#include "../input.h"
#include "../store.h"
#include "../context.h"
#include "../kvutils.h"
#include "../app.h"

#include "mere/utils/merestringutils.h"

MSet::MSet(QObject *parent)
    : MSet("", parent)
{

}

MSet::MSet(QString argument, QObject *parent)
    : Command(Command::MSet, argument, parent)
{

}

bool MSet::execute() const
{
    //qDebug() << "Going to run " << this->command() << " with the arguments " << this->argument();

    bool ok = false;

    QList<QPair<QString, QString>> pairs;

    try
    {
        pairs = KVUtils::pairs(this->argument());
    }
    catch (...)
    {
        qDebug() << "Exception....";
    }


    QString storeName = App::context()->store();

    Store store(storeName);

    QListIterator<QPair<QString, QString>> it(pairs);

    while(it.hasNext())
    {
        QPair<QString, QString> pair = it.next();

        if (MereStringUtils::isBlank(pair.second))
        {
            // when there is only one argument
            // then the key is considered as value
            // system will auto-generate the key
            ok = store.set(pair.first);
        }
        else
        {
            ok = store.set(pair.first, pair.second);
        }
    }

    return ok;
}

void MSet::help() const
{
    qDebug() <<  "THIS IS A TEST";
}
