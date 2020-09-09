#include "command.h"
#include "command/alias.h"
#include "command/close.h"
#include "command/config.h"
#include "command/create.h"
#include "command/del.h"
#include "command/get.h"
#include "command/help.h"
#include "command/history.h"
#include "command/insert.h"
#include "command/list.h"
#include "command/mdel.h"
#include "command/mget.h"
#include "command/mset.h"
#include "command/remove.h"
#include "command/select.h"
#include "command/set.h"
#include "command/void.h"
#include "command/what.h"

const QString Command::Alias  = "alias";
const QString Command::Close  = "close";
const QString Command::Config = "config";
const QString Command::Create = "create";
const QString Command::Del    = "del";
const QString Command::Exit   = "exit";
const QString Command::Get    = "get";
const QString Command::Help   = "help";
const QString Command::History= "history";
const QString Command::Insert = "insert";
const QString Command::List   = "list";
const QString Command::MDel   = "mdel";
const QString Command::MGet   = "mget";
const QString Command::MSet   = "mset";
const QString Command::Quit   = "quit";
const QString Command::Remove = "remove";
const QString Command::Select = "select";
const QString Command::Set    = "set";
const QString Command::Void   = "void";
const QString Command::What   = "what";

QHash<QString, Command *> Command::m_commands =
{
    {Command::Alias,    0},
    {Command::Close,    0},
    {Command::Config,   0},
    {Command::Create,   0},
    {"create.store",    0},
    {Command::Del,      0},
    {Command::Get,      0},
    {Command::Help,     0},
    {Command::History,  0},
    {Command::Insert,   0},
    {Command::List,     0},
    {Command::MDel,     0},
    {Command::MGet,     0},
    {Command::MSet,     0},
    {Command::Remove,   0},
    {"remove.store",    0},
    {Command::Select,   0},
    {Command::Set,      0},
    {Command::Void,     new class Void()},
    {Command::What,     0}
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

//static
Command* Command::get(const QString &key)
{
    Command *command = m_commands.value(key);
    if (command == NULL)
    {
        if (m_commands.contains(key))
        {
            if(key.compare(Command::Alias) == 0)
                command = new class Alias();
            else if(key.compare(Command::Close) == 0)
                command = new class Close();
            else if(key.compare(Command::Config) == 0)
                command = new class Config();
            else if(key.compare(Command::Create) == 0)
                command = new class Create();
            else if(key.compare(Command::Del) == 0)
                command = new class Del();
            else if(key.compare(Command::Get) == 0)
                command = new class Get();
            else if(key.compare(Command::Help) == 0)
                command = new class Help();
            else if(key.compare(Command::History) == 0)
                command = new class History();
            else if(key.compare(Command::Insert) == 0)
                command = new class Insert();
            else if(key.compare(Command::List) == 0)
                command = new class List();
            else if(key.compare(Command::MDel) == 0)
                command = new class MDel();
            else if(key.compare(Command::MGet) == 0)
                command = new class MGet();
            else if(key.compare(Command::MSet) == 0)
                command = new class MSet();
            else if(key.compare(Command::Remove) == 0)
                command = new class Remove();
            else if(key.compare(Command::Select) == 0)
                command = new class Select();
            else if(key.compare(Command::Set) == 0)
                command = new class Set();
            else if(key.compare(Command::What) == 0)
                command = new class What();

            m_commands[key] = command;
        }
        else
            command = m_commands.value(Command::Void);
    }

    return command;
}

//static
bool Command::has(const QString &key)
{
    return m_commands.contains(key);
}
