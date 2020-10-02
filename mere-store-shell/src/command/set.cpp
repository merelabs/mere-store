#include "set.h"
#include "../shell.h"
#include "../context.h"
#include "../store.h"
#include "../slice.h"
#include "../parser.h"

#include "mere/utils/merestringutils.h"

#include <QCommandLineParser>

Set::Set(QObject *parent)
    : Set("", parent)
{

}

Set::Set(QString argument, QObject *parent)
    : Command(Command::Set, argument, parent)
{

}

bool Set::execute() const
{
    //qDebug() << "Going to run " << this->command() << " with the arguments " << this->argument();

    bool ok = false;

    QString store = Shell::context()->store();
    if (MereStringUtils::isBlank(store))
    {
        QString slice = Shell::context()->slice();
        if (MereStringUtils::isBlank(slice))
        {
            QTextStream(stdout) << "Did you mean to set key/value from a store or a slice?" << Qt::endl
                                << "Run 'help set' for more information." << Qt::endl;
        }
        return ok;
    }

    QString type = "";
    QString key  = "";
    QString value= "";

    Parser parser(this->argument(), QStringList({"-j","-m"}));

    QStringRef ref = parser.next();

    if (parser.isOption())
        type = ref.toString();
    else
        key = ref.toString();

    if(MereStringUtils::isBlank(key))
    {
        QStringRef ref = parser.next();
        key = ref.toString();
    }

    ref = parser.rest();
    value = ref.toString();

    if (MereStringUtils::isBlank(key) && MereStringUtils::isBlank(value))
    {
        QTextStream(stdout) << "Please provide key and value to persist to the store or slice." << Qt::endl
                            << "Run 'help set' for more information." << Qt::endl;
        return ok;
    }

    ok = set(key, value, type);

    return ok;
}

QString Set::type(const QString &option) const
{
    QString type;

    QChar ch = option.at(1);
    switch (ch.unicode())
    {
        case 'j':
            type = "json";
            break;

        case 'm':
            type = "mson";
            break;

        default:
            type ="";
            break;

    }

    return type;
}

bool Set::set(const QString &key, const QString &value, const QString &type) const
{
    bool ok = false;

    if (MereStringUtils::isBlank(Shell::context()->slice()))
        ok = setStore(key, value, type);
    else
        ok = setSlice(key, value, type);

    return ok;
}

bool Set::setStore(const QString &key, const QString &value, const QString &type) const
{
    bool ok = false;

    QString storeName = Shell::context()->store();
    Store store(storeName);

    if (MereStringUtils::isBlank(value))
        ok = store.set(key, type);
    else
        ok = store.set(key, value, type);

    return ok;
}

bool Set::setSlice(const QString &key, const QString &value, const QString &type) const
{
    bool ok = false;

    QString storeName = Shell::context()->store();
    QString sliceName = Shell::context()->slice();

    Slice slice(storeName, sliceName);

    if (MereStringUtils::isBlank(value))
        ok = slice.set(key, type);
    else
        ok = slice.set(key, value, type);

    return ok;
}
