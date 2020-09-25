#include "switch.h"
#include "../shell.h"
#include "../context.h"

#include "mere/utils/merestringutils.h"

Switch::Switch(QObject *parent)
    : Switch("", parent)
{

}

Switch::Switch(QString argument, QObject *parent)
    : Command(Command::Switch, argument, parent)
{
    connect(this, SIGNAL(switched(const QString&)), Shell::context(), SLOT(switched(const QString&)));
}

bool Switch::execute() const
{
    //qDebug() << "Going to run " << this->command() << " with the arguments " << this->argument();

    QString argument = this->argument();
    if (MereStringUtils::isBlank(argument))
    {
        QString message = "";
        if (MereStringUtils::isNotBlank(Shell::context()->slice()))
        {
            message = "Did you mean to switch to another slice?\nRun 'help switch' for more details.";
        }
        else if (MereStringUtils::isNotBlank(Shell::context()->store()))
        {
            message = "Did you mean to switch to another store?\nRun 'help switch' for more details.";
        }
        else
        {
            message = "Did you mean to switch to store or slice?\nRun 'help switch' or 'help select' for more details.";
        }

        QTextStream(stdout) << message << Qt::endl;

        return false;
    }

    if (MereStringUtils::isNotBlank(Shell::context()->slice()))
    {
        argument = argument.prepend("slice ");
    }
    else if (MereStringUtils::isNotBlank(Shell::context()->store()))
    {
        argument = argument.prepend("store ");
    }
    else
    {
        QTextStream(stdout) << "Did you mean to switch to store or slice?" << Qt::endl
                            << "Run 'help switch' or 'help select' for more details." << Qt::endl;
        return false;
    }

    Command *command = Command::get(Command::Select);
    command->setArgument(argument);

    return command->execute();
}
