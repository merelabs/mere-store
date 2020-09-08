#include "help.h"

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


    const QString key = this->argument();
    if (MereStringUtils::isBlank(key) || !Command::has(key))
    {
        help();
    }
    else
    {
        Command *command = Command::get(key);
        command->help();
    }

    return ok;
}
