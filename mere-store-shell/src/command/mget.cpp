#include "mget.h"
#include "../input.h"
#include "../store.h"
#include "../context.h"
#include "../kvutils.h"
#include "../shell.h"

#include "mere/utils/stringutils.h"

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
        QTextStream(stdout) << "Exception...." << Qt::endl;
        return false;
    }

    QString storeName = Shell::context()->store();
    Store store(storeName);

    QListIterator<QString> it(keys);
    while(it.hasNext())
    {
        QString key = it.next();
        QVariant value = store.get(key);
        QTextStream(stdout) << "-" << key << value.toString() << Qt::endl;
    }

    return ok;
}
