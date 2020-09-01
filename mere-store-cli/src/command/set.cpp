#include "set.h"
#include "../input.h"
#include "../store.h"
#include "../context.h"
#include "../kvutils.h"
#include "../merestorecli.h"

#include "mere/utils/merestringutils.h"

Set::Set(QObject *parent)
    : Set("", parent)
{

}

Set::Set(QString argument, QObject *parent)
    : Command(Command::Set, argument, parent)
{

}

bool Set::execute() const
{
    qDebug() << "Going to run " << this->command() << " with the arguments " << this->argument();

    bool ok = false;

    QList<QPair<QString, QString>> pairs;

    try
    {
        pairs = KVUtils::split(this->argument());
    }
    catch (...)
    {
        qDebug() << "Exception....";
    }


    QString storeName = MereCli::context()->get();

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
