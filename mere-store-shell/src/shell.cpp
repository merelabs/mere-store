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

        while (1)
        {
            QString line = m_prompt->accept();

            if (line.compare(Command::Exit) == 0 | line.compare(Command::Quit) == 0)
                break;

            Input input(line);
            input.process();
        }
        exit();
    });

    return true;
}

Context* Shell::context()
{
    return globalContext;;
}
