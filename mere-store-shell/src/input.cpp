#include "input.h"
#include "command.h"
#include "command/alias.h"
#include "command/history.h"
#include "command/alias.h"

#include "mere/utils/stringutils.h"

Input::~Input()
{

}

Input::Input(const QString &input, QObject *parent)
    : Processor(input, parent)
{
}

bool Input::process()
{
    if (Mere::Utils::StringUtils::isBlank(this->input()))
        return false;

    const QString key = this->command();
    if (Alias::has(key))
    {
        const QString line(Alias::alias(key) + " " + this->argument());
        Input input(line);
        return input.process();
    }

    // append to the command history
    History::append(this->input());

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
    if (!Mere::Utils::StringUtils::isBlank(input))
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
    if (!Mere::Utils::StringUtils::isBlank(input))
    {
        int pos = input.indexOf(" ");
        if (pos > -1)
            argument = input.mid(pos + 1).trimmed();
    }

    return argument;
}
