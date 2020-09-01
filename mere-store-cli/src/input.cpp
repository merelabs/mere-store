#include "input.h"
#include "command.h"

#include "mere/utils/merestringutils.h"

Input::Input(const QString &input, QObject *parent)
    : Processor(input, parent)
{

}

bool Input::process()
{
    qDebug() << "Going to process " << this->command();

    const QString key = this->command();
    Command *command = Command::get(key);
    if (command == NULL)
        return false;

    command->setArgument(this->argument());

    return command->execute();
}

QString Input::command() const
{
    QString command = Command::Void;

    QString input = this->input();
    if (!MereStringUtils::isBlank(input))
    {
        QStringList parts = input.split(" ");

        if (!parts.isEmpty())
            command = parts.first();
    }

    return command;
}

QString Input::argument() const
{
    QString argument = "";

    QString input = this->input();
    if (!MereStringUtils::isBlank(input))
    {
        int pos = input.indexOf(" ");
        if (pos > -1)
            argument = input.mid(pos + 1).trimmed();
    }

    return argument;
}
