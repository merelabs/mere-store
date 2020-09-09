#include "shell.h"
#include "input.h"
#include "prompt.h"
#include "context.h"
#include "command.h"
#include "linereader.h"

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
    m_prompt->welcome();

    //LineReader reader;
    //reader.read();

    QString line;
    do
    {
        line = m_prompt->accept();

        Input input(line);
        input.process();
    } while (line.compare(Command::Exit) && line.compare(Command::Quit));

    ::exit(0);

    return true;
}

Context* Shell::context()
{
    return globalContext;;
}
