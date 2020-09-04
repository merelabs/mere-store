#include "create.h"
#include "../store.h"
#include "../slice.h"
#include "../context.h"
#include "../app.h"
#include "../kvutils.h"

Create::Create(QObject *parent)
    : Create("", parent)
{

}

Create::Create(QString argument, QObject *parent)
    : Command(Command::Create, argument, parent)
{

}

bool Create::execute() const
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
        qDebug() << "Exception....";
    }

    QString object = blocks.at(0);
    if (object.compare("store") == 0)
    {
        ok = createStore(blocks.at(1));
    }
    else if (object.compare("store") == 0)
    {
        QString store = App::context()->store();
        ok = createSlice(store, blocks.at(1));
    }

    return ok;
}

bool Create::createStore(const QString &store) const
{
    bool ok = false;

    Store s(store);
    ok = s.create();

    if (ok)
    {
        qDebug() << "Store " << store << " created successfully.";
        s.close();
    }
    else
        qDebug() << "Store " << store << " already exists.";

    return ok;
}

bool Create::createSlice(const QString &store, const QString &slice) const
{
    bool ok = false;

    Slice s(store, slice);
    ok = s.create();

    if (ok)
    {
        qDebug() << "Slice " << slice << " of " << store << " created successfully.";
        //s.close();
    }
    else
        qDebug() << "Slice " << slice << " of " << store << " already exists.";

    return ok;

}
