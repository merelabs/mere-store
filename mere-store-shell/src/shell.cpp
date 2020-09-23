#include "shell.h"
#include "input.h"
#include "prompt.h"
#include "context.h"
#include "command.h"

#include <QTimer>
#include <QDebug>

Q_GLOBAL_STATIC(Context, globalContext)

Shell::Shell(int argc, char *argv[])
    : QCoreApplication(argc, argv)
{
    m_prompt = new Prompt(globalContext);
}

bool Shell::init()
{
    return true;
}

bool Shell::start()
{
    QTimer::singleShot(0, [this](){
        m_prompt->welcome();

        QString line;
        do
        {
            Input input(line);
            input.process();

            line = m_prompt->accept();
        } while (line.compare(Command::Exit) && line.compare(Command::Quit));
        exit();
    });

    return true;
}

Context* Shell::context()
{
    return globalContext;;
}
