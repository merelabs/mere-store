#include "list.h"
#include "../store.h"
#include "../slice.h"
#include "../context.h"
#include "../shell.h"

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

    QVariant list = this->list();

    QMap<QString, QVariant> map = list.toMap();
    QMapIterator<QString, QVariant> it(map);
    while (it.hasNext())
    {
        it.next();
        QTextStream(stdout) << "- " << it.key() << " : " << it.value().toString() << endl;
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
