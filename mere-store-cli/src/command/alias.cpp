#include "alias.h"
#include "../kvutils.h"

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

    QList<QString> blocks;

    try
    {
        blocks = KVUtils::blocks(this->argument());
    }
    catch (...)
    {
        qDebug() << "Exception....";
    }

    const QString alias   = blocks.at(0);
    const QString command = blocks.at(1);

    m_commands.insert(alias, command);

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

void Alias::help() const
{
    qDebug() <<  "THIS IS A TEST";
}
