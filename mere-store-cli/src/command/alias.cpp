#include "alias.h"
#include "../command.h"
#include "../kvutils.h"

#include "mere/utils/merestringutils.h"

QHash<QString, QString> Alias::m_commands;

Alias::Alias(QObject *parent)
    : Alias("", parent)
{

}

Alias::Alias(QString argument, QObject *parent)
    : Command(Command::Alias, argument, parent)
{

}

bool Alias::execute() const
{
    //qDebug() << "Going to run " << this->command() << " with the arguments " << this->argument();

    bool ok = true;

    if (!MereStringUtils::isBlank(this->argument()))
    {
        int pos = this->argument().indexOf(" ");
        if (pos != -1)
            add(this->argument().left(pos), this->argument().mid(pos + 1));
        else
            show(this->argument());
    }
    else
    {
        show();
    }

    return ok;
}

//static
bool Alias::has(const QString &key)
{
    return Alias::m_commands.contains(key);
}

//static
QString Alias::alias(const QString &key)
{
    return Alias::m_commands.value(key);
}

void Alias::show() const
{
    QTextStream out(stdout);
    QHashIterator<QString, QString> it(Alias::m_commands);
    while (it.hasNext())
    {
        it.next();

        out << "- " << it.key() << " " << it.value() << endl;
    }
}

void Alias::show(const QString &alias) const
{
    QTextStream out(stdout);
    out << "- " << alias << this->alias(alias) << endl;
}

void Alias::add(const QString &alias, const QString &command) const
{
    m_commands.insert(alias, command);
}

void Alias::help() const
{
    qDebug() <<  "THIS IS A TEST";
}
