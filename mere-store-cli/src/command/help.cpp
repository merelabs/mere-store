#include "help.h"
#include "../kvutils.h"

#include "mere/utils/merestringutils.h"

Help::Help(QObject *parent)
    : Help("", parent)
{

}

Help::Help(QString argument, QObject *parent)
    : Command(Command::Help, argument, parent)
{

}
bool Help::execute() const
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

    if (blocks.size() == 0)
    {
        help();
    }
    else
    {
        const QString key = blocks.at(0);
        if (MereStringUtils::isBlank(key) || !Command::has(key))
        {
            help();
        }
        else
        {
            Command *command = Command::get(key);
            command->help();
        }
    }

    return ok;
}
