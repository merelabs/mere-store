#include "mget.h"
#include "../input.h"
#include "../store.h"
#include "../context.h"
#include "../kvutils.h"
#include "../app.h"

#include "mere/utils/merestringutils.h"

MGet::MGet(QObject *parent)
    : MGet("", parent)
{

}

MGet::MGet(QString argument, QObject *parent)
    : Command(Command::MGet, argument, parent)
{

}

bool MGet::execute() const
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


    QString storeName = App::context()->store();
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
