#include "del.h"
#include "../input.h"
#include "../store.h"
#include "../slice.h"
#include "../context.h"
#include "../kvutils.h"
#include "../shell.h"

#include "mere/utils/merestringutils.h"

Del::Del(QObject *parent)
    : Del("", parent)
{

}

Del::Del(QString argument, QObject *parent)
    : Command(Command::Del, argument, parent)
{

}

bool Del::execute() const
{
    bool ok = false;

    QString store = Shell::context()->store();
    if (MereStringUtils::isBlank(store))
    {
        QString slice = Shell::context()->slice();
        if (MereStringUtils::isBlank(slice))
        {
            QTextStream(stdout) << "Did you mean to del key from a store or a slice?" << Qt::endl
                                << "Run 'help del' for more information." << Qt::endl;
        }
        return ok;
    }

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

    QTextStream(stdout) << "Do you want to delete? [y/N] : ";

    QTextStream input(stdin);
    QString answer = input.readLine(1);
    if (answer.toLower().compare("y") == 0)
    {
        if(keys.size() == 1)
            del(keys.at(0));
        else
            del(keys);
    }

    return ok;
}

bool Del::del(const QString &key) const
{
    bool ok = false;

    if (MereStringUtils::isBlank(Shell::context()->slice()))
        ok = delStore(key);
    else
        ok = delSlice(key);

    return ok;
}

bool Del::del(const QList<QString> &keys) const
{
    bool ok = false;

    if (MereStringUtils::isBlank(Shell::context()->slice()))
        ok = delStore(keys);
    else
        ok = delSlice(keys);

    return ok;
}

bool Del::delStore(const QString &key) const
{
    bool ok = false;

    QString storeName = Shell::context()->store();
    Store store(storeName);

    ok = store.del(key);

    return ok;
}

bool Del::delSlice(const QString &key) const
{
    bool ok = false;

    QString storeName = Shell::context()->store();
    QString sliceName = Shell::context()->slice();
    Slice slice(storeName, sliceName);

    ok = slice.del(key);

    return ok;
}

bool Del::delStore(const QList<QString> &keys) const
{
    bool ok = false;

    QString storeName = Shell::context()->store();
    Store store(storeName);

    ok = store.del(keys);

    return ok;
}

bool Del::delSlice(const QList<QString> &keys) const
{
    bool ok = false;

    QString storeName = Shell::context()->store();
    QString sliceName = Shell::context()->slice();
    Slice slice(storeName, sliceName);

    ok = slice.del(keys);

    return ok;
}
