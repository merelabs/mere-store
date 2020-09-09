#include "select.h"
#include "../store.h"
#include "../slice.h"
#include "../context.h"
#include "../kvutils.h"
#include "../shell.h"

#include "mere/store/merestore.h"

Select::Select(QObject *parent)
    : Select("", parent)
{

}

Select::Select(QString argument, QObject *parent)
    : Command(Command::Select, argument, parent)
{
    connect(this, SIGNAL(selected(const QString&, const QString&)), Shell::context(), SLOT(selected(const QString&, const QString&)));
}

bool Select::execute() const
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

    if (blocks.size() == 0)
    {
        QTextStream(stdout) << "Did you mean to select store or slice? Run help select for more information." << endl;
        return ok;
    }

    QString object = blocks.at(0);
    if (Mere::Store::Type::STORE.compare(object) == 0)
    {
        ok = selectStore(blocks.at(1));
    }
    else if (Mere::Store::Type::SLICE.compare(object) == 0)
    {
        QString store = Shell::context()->store();
        ok = selectSlice(store, blocks.at(1));
    }
    else
    {
        QTextStream(stdout) << "Did you mean to create store or slice? Run help create for more information." << endl;
    }

    return ok;
}

bool Select::selectStore(const QString &store) const
{
    bool ok = false;

    Store s(store);
    ok = s.select();

    if (ok)
    {
        qDebug() << "Store " << store << " selected successfully.";
        s.close();
        emit selected(Mere::Store::Type::STORE, store);
    }
    else
        qDebug() << "Store " << store << " does not exists.";

    return ok;
}

bool Select::selectSlice(const QString &store, const QString &slice) const
{
    bool ok = false;

    Slice s(store, slice);
    ok = s.select();

    if (ok)
    {
        qDebug() << "Slice " << slice << " selected successfully.";
        s.close();
        emit selected(Mere::Store::Type::SLICE, slice);
    }
    else
        qDebug() << "Slice " << slice << " does not exists.";

    return ok;
}
