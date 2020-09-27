#include "list.h"
#include "../store.h"
#include "../slice.h"
#include "../context.h"
#include "../shell.h"
#include "../kvutils.h"

#include "mere/utils/merestringutils.h"

List::List(QObject *parent)
    : List("", parent)
{

}

List::List(QString argument, QObject *parent)
  : Command(Command::List, argument, parent)
{

}

bool List::execute() const
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
        QTextStream(stdout) << "Exception...." << Qt::endl;
        return false;
    }

    QVariant list;

    if (blocks.size() == 0)
    {
        list = this->list();
    }
    else if (blocks.size() == 1)
    {
        QString arg = blocks.at(0);

        if (MereStringUtils::isInteger(arg))
            list = this->list(arg.toInt());
        else
            list = this->list(arg);
    }
    else if (blocks.size() == 2 &&
             !blocks.contains("-k") &&
             !blocks.contains("--key") &&
             !blocks.contains("-v") &&
             !blocks.contains("--value") &&
             !blocks.contains("-l") &&
             !blocks.contains("--limit"))
    {
        list = this->list(blocks.at(0), blocks.at(1).toInt());
    }

    QMap<QString, QVariant> map = list.toMap();
    QMapIterator<QString, QVariant> it(map);
    while (it.hasNext())
    {
        it.next();
        QTextStream(stdout) << "- " << it.key() << " : " << it.value().toString() << Qt::endl;
    }

    return ok;
}

QVariant List::list() const
{
    QVariant list;

    QString store = Shell::context()->store();
    QString slice = Shell::context()->slice();

    if(MereStringUtils::isBlank(slice))
    {
        Store s(store);
        list = s.list();
    }
    else
    {
        Slice s(store, slice);
        list = s.list();
    }

    return list;
}

QVariant List::list(const uint &limit) const
{
    QVariant list;

    QString store = Shell::context()->store();
    QString slice = Shell::context()->slice();

    if(MereStringUtils::isBlank(slice))
    {
        Store s(store);
        list = s.list(limit);
    }
    else
    {
        Slice s(store, slice);
        list = s.list(limit);
    }

    return list;
}

QVariant  List::list(const QString &key) const
{
    QVariant list;

    QString store = Shell::context()->store();
    QString slice = Shell::context()->slice();

    if(MereStringUtils::isBlank(slice))
    {
        Store s(store);
        list = s.list(key);
    }
    else
    {
        Slice s(store, slice);
        list = s.list(key);
    }

    return list;
}

QVariant  List::list(const QString &key, const uint &limit) const
{
    QVariant list;

    QString store = Shell::context()->store();
    QString slice = Shell::context()->slice();

    if(MereStringUtils::isBlank(slice))
    {
        Store s(store);
        list = s.list(key, limit);
    }
    else
    {
        Slice s(store, slice);
        list = s.list(key, limit);
    }

    return list;
}


