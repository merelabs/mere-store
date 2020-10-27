#include "select.h"
#include "../store.h"
#include "../slice.h"
#include "../context.h"
#include "../kvutils.h"
#include "../shell.h"

#include "mere/store/store/store.h"

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
        QTextStream(stdout) << "Did you mean to select store or slice? Run 'help select' for more information." << Qt::endl;
        return false;
    }

    if (blocks.size() > 2)
    {
        QTextStream(stdout) << "Too many arguments to select store or slice. Run 'help select' for more information." << Qt::endl;
        return false;
    }

    bool ok = false;

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
        QTextStream(stdout) << "Did you mean to create store or slice? Run help create for more information." << Qt::endl;
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
        QTextStream(stdout) << "Store " << store << " selected successfully." << Qt::endl;
        s.close();
        emit selected(Mere::Store::Type::STORE, store);
    }
    else
        QTextStream(stdout) << "Store " << store << " does not exists." << Qt::endl;

    return ok;
}

bool Select::selectSlice(const QString &store, const QString &slice) const
{
    bool ok = false;

    Slice s(store, slice);
    ok = s.select();

    if (ok)
    {
        QTextStream(stdout) << "Slice " << slice << " selected successfully." << Qt::endl;
        s.close();
        emit selected(Mere::Store::Type::SLICE, slice);
    }
    else
        QTextStream(stdout) << "Slice " << slice << " does not exists." << Qt::endl;

    return ok;
}
