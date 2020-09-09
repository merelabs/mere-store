#include "set.h"
#include "../shell.h"
#include "../context.h"
#include "../store.h"
#include "../slice.h"

#include "mere/utils/merestringutils.h"

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

//    QString store = Shell::context()->store();
//    if (MereStringUtils::isBlank(store))
//    {
//        QTextStream(stdout) << "Did you mean to set key/value to a store or a slice?" << endl
//                            << "Run 'help set' for more information." << endl;
//        return ok;
//    }

    QString type  = this->type();
    QString key   = this->key();
    QString value = this->value();

    if (MereStringUtils::isBlank(key) && MereStringUtils::isBlank(value))
    {
        QTextStream(stdout) << "Did you mean to set key/value for a store or a slice?" << endl
                            << "Please provide key and value to persist to the store or slice." << endl
                            << "Run 'help set' for more information." << endl;
        return ok;
    }

    ok = set(key, value, type);

    return ok;
}

QString Set::type() const
{
    QString type("string");

    if(this->argument().startsWith("-"))
    {
        QChar ch = this->argument().at(1);
        switch (ch.unicode())
        {
            case 'j':
                type = "json";
                break;

            case 'm':
                type = "mson";
                break;

            default:
                type ="string";
                break;

        }
    }

    return type;
}

QString Set::key() const
{
    QString key;

    int pos = this->argument().indexOf(" ");
    if(pos != -1)
        key = this->argument().left(pos);

    return key;
}

QString Set::value() const
{
    QString value;

    int pos = this->argument().indexOf(" ");
    if(pos != -1)
        value = this->argument().mid(pos + 1);

    return value;
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
        ok = store.set(key);
    else
        ok = store.set(key, value);

    return ok;
}

bool Set::setSlice(const QString &key, const QString &value, const QString &type) const
{
    bool ok = false;

    QString storeName = Shell::context()->store();
    QString sliceName = Shell::context()->slice();
    Slice slice(storeName, sliceName);

    if (MereStringUtils::isBlank(value))
        ok = slice.set(key);
    else
        ok = slice.set(key, value);

    return ok;
}
