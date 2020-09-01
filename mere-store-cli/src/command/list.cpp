#include "list.h"
#include "../store.h"
#include "../context.h"
#include "../merestorecli.h"

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
    qDebug() << "Going to run " << this->command() << " with the arguments " << this->argument();

    bool ok = false;

    QString storeName = MereCli::context()->get();

//    if (this->object().compare("store") == 0)
//    {
        Store store(storeName);
        QVariant value = store.list();

        qDebug() << "Store " << value;

//        if (ok)
//        {
//            qDebug() << "Store " << this->subject() << " created successfully.";
//            store.close();
//        }
//        else
//            qDebug() << "Store " << this->subject() << " already exists.";
//    }

    return ok;

}

