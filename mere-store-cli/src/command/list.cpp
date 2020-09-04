#include "list.h"
#include "../store.h"
#include "../context.h"
#include "../app.h"

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

    QString storeName = App::context()->store();

    Store store(storeName);
    QVariant value = store.list();

    qDebug() << "Store " << value;

    return ok;
}

void List::help() const
{
    qDebug() <<  "THIS IS A TEST";
}
