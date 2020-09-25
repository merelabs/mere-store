#include "get.h"
#include "../input.h"
#include "../store.h"
#include "../slice.h"
#include "../context.h"
#include "../kvutils.h"
#include "../shell.h"

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
        QTextStream(stdout) << "Exception...." << Qt::endl;
        return false;
    }

    QListIterator<QString> it(keys);
    while(it.hasNext())
    {
        QString key    = it.next();
        QVariant value = get(key);
        QTextStream(stdout) << "- " << key << " : " << value.toString() << Qt::endl;
    }

    return ok;
}


QVariant Get::get(const QString &key) const
{
    QVariant val;

    if (MereStringUtils::isBlank(Shell::context()->slice()))
        val = getStore(key);
    else
        val = getSlice(key);

    return val;
}

QVariant Get::getStore(const QString &key) const
{
    QString storeName = Shell::context()->store();
    Store store(storeName);

    return store.get(key);
}

QVariant Get::getSlice(const QString &key) const
{
    QString storeName = Shell::context()->store();
    QString sliceName = Shell::context()->slice();

    Slice slice(storeName, sliceName);

    return slice.get(key);
}
