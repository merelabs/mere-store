#include "remove.h"
#include "../store.h"
#include "../slice.h"
#include "../shell.h"
#include "../context.h"
#include "../kvutils.h"

#include "mere/store/store.h"
#include "mere/utils/merestringutils.h"

Remove::Remove(QObject *parent)
    : Remove("", parent)
{

}

Remove::Remove(QString argument, QObject *parent)
    : Command(Command::Remove, argument, parent)
{

}

bool Remove::execute() const
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
        QTextStream(stdout) << "Did you mean to remove store or slice? Run help remove for more information." << Qt::endl;
        return ok;
    }

    QString object = blocks.at(0);
    if (Mere::Store::Type::STORE.compare(object) == 0)
    {
        blocks.removeFirst();
        ok = removeStores(blocks);
    }
    else if (Mere::Store::Type::SLICE.compare(object) == 0)
    {
        QString store = Shell::context()->store();
        if (MereStringUtils::isBlank(store))
        {
            QTextStream(stdout) << "To delete a slice, select the store first." << Qt::endl
                                << "Run 'help select' or 'help remove' for more information." << Qt::endl;
            return ok;
        }

        blocks.removeFirst();
        ok = removeSlices(store, blocks);
    }
    else
    {
        QTextStream(stdout) << "Did you mean to remove store or slice? Run help remove for more information." << Qt::endl;
    }

    return ok;
}

bool Remove::removeStore(const QString &store) const
{
    bool ok = false;

    Store s(store);
    ok = s.remove();

    if (ok)
    {
        QTextStream(stdout) << "Store " << store << " remove successfully." << Qt::endl;
    }
    else
        QTextStream(stdout) << "Store " << store << " does not exists." << Qt::endl;

    return ok;
}

bool Remove::removeStores(const QList<QString> &stores) const
{
    bool ok = false;

    QListIterator<QString> it(stores);
    while (it.hasNext())
    {
        QString store = it.next();
        ok = removeStore(store);
    }

    return ok;
}

bool Remove::removeSlice(const QString &store, const QString &slice) const
{
    bool ok = false;

    Slice s(store, slice);
    ok = s.remove();

    if (ok)
    {
        QTextStream(stdout) << "Slice " << slice << " of " << store << " removed successfully." << Qt::endl;
    }
    else
        QTextStream(stdout) << "Slice " << slice << " of " << store << " does not exists." << Qt::endl;

    return ok;

}

bool Remove::removeSlices(const QString &store, const QList<QString> &slices) const
{
    bool ok = false;

    QListIterator<QString> it(slices);
    while (it.hasNext())
    {
        QString slice = it.next();
        ok = removeSlice(store, slice);
    }

    return ok;
}

