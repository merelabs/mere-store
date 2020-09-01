#include "command.h"
#include "close.h"
#include "config.h"
#include "create.h"
#include "del.h"
#include "get.h"
#include "insert.h"
#include "list.h"
#include "remove.h"
#include "select.h"
#include "set.h"
#include "void.h"
#include "../context.h"

const QString Command::Close  = "close";
const QString Command::Config = "config";
const QString Command::Create = "create";
const QString Command::Del    = "del";
const QString Command::Exit   = "exit";
const QString Command::Get    = "get";
const QString Command::Insert = "insert";
const QString Command::List   = "list";
const QString Command::Quit   = "quit";
const QString Command::Remove = "remove";
const QString Command::Select = "select";
const QString Command::Set    = "set";
const QString Command::Void   = "void";

QHash<QString, Command *> Command::m_commands =
{
    {Command::Close, 0},
    {Command::Config, 0},
    {Command::Create, 0},
    {"create.store", 0},
    {Command::Get, 0},
    {Command::Insert, 0},
    {Command::List, 0},
    {Command::Remove, 0},
    {"remove.store", 0},
    {Command::Select, 0},
    {Command::Set, 0},
    {Command::Void, new class Void()}
};

Command::Command(QString command, QString argument, QObject *parent)
    : QObject(parent),
      m_command (command),
      m_argument (argument)
{

}

QString Command::command() const
{
    return m_command;
}

void Command::setArgument(const QString argument)
{
    m_argument = argument;
}

QString Command::argument() const
{
    return m_argument;
}

Command* Command::get(const QString &key)
{
    Command *command = m_commands.value(key);
    if (command == NULL)
    {
        if (m_commands.contains(key))
        {
            if(key.compare(Command::Close) == 0)
                command = new class Close();
            else if(key.compare(Command::Config) == 0)
                command = new class Config();
            else if(key.compare(Command::Create) == 0)
                command = new class Create();
            else if(key.compare(Command::Del) == 0)
                command = new class Del();
            else if(key.compare(Command::Get) == 0)
                command = new class Get();
            else if(key.compare(Command::Insert) == 0)
                command = new class Insert();
            else if(key.compare(Command::List) == 0)
                command = new class List();
            else if(key.compare(Command::Remove) == 0)
                command = new class Remove();
            else if(key.compare(Command::Select) == 0)
                command = new class Select();
            else if(key.compare(Command::Set) == 0)
                command = new class Set();

            m_commands[key] = command;
        }
        else
            command = m_commands.value(Command::Void);
    }
    return command;
}
