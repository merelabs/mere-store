#include "create.h"
#include "../store.h"
#include "../slice.h"
#include "../shell.h"
#include "../context.h"
#include "../kvutils.h"

#include "mere/store/store.h"
#include "mere/utils/merestringutils.h"

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
        QTextStream(stdout) << "Exception...." << Qt::endl;
        return false;
    }

    if (blocks.size() == 0)
    {
        QTextStream(stdout) << "Did you mean to create store or slice? Run help create for more information." << Qt::endl;
        return ok;
    }

    QString object = blocks.at(0);
    if (Mere::Store::Type::STORE.compare(object) == 0)
    {
        blocks.removeFirst();
        ok = createStores(blocks);
    }
    else if (Mere::Store::Type::SLICE.compare(object) == 0)
    {
        blocks.removeFirst();
        QString store = Shell::context()->store();
        ok = createSlices(store, blocks);
    }
    else
    {
        QTextStream(stdout) << "Did you mean to create store or slice? Run help create for more information." << Qt::endl;
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
        QTextStream(stdout) << "Store " << store << " created successfully." << Qt::endl;
        s.close();
    }
    else
        QTextStream(stdout) << "Store " << store << " already exists." << Qt::endl;

    return ok;
}

bool Create::createStores(const QList<QString> &stores) const
{
    bool ok = false;

    QListIterator<QString> it(stores);
    while (it.hasNext())
    {
        QString store = it.next();
        ok = createStore(store);
    }

    return ok;
}

bool Create::createSlice(const QString &store, const QString &slice) const
{
    bool ok = false;

    Slice s(store, slice);
    ok = s.create();

    if (ok)
    {
        QTextStream(stdout) << "Slice " << slice << " of " << store << " created successfully." << Qt::endl;
    }
    else
        QTextStream(stdout) << "Slice " << slice << " of " << store << " already exists." << Qt::endl;

    return ok;

}

bool Create::createSlices(const QString &store, const QList<QString> &slices) const
{
    bool ok = false;

    if (MereStringUtils::isBlank(store))
    {
        QTextStream(stdout) << "Slice is a part of a store, select a store before creating a slice." << Qt::endl
                            << "Run 'help create' or 'help select' for more information." << Qt::endl;

        return ok;
    }

    QListIterator<QString> it(slices);
    while (it.hasNext())
    {
        QString slice = it.next();
        ok = createSlice(store, slice);
    }

    return ok;
}
