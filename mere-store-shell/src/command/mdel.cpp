#include "mdel.h"
#include "../input.h"
#include "../store.h"
#include "../context.h"
#include "../kvutils.h"
#include "../shell.h"

#include "mere/utils/merestringutils.h"

MDel::MDel(QObject *parent)
    : MDel("", parent)
{

}

MDel::MDel(QString argument, QObject *parent)
    : Command(Command::MDel, argument, parent)
{

}

bool MDel::execute() const
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


    QString storeName = Shell::context()->store();
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
