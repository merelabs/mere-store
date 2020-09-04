#include "app.h"
#include "input.h"
#include "prompt.h"
#include "context.h"
#include "command.h"
#include "linereader.h"

Q_GLOBAL_STATIC(Context, globalContext)

App::App(int argc, char *argv[])
    : QCoreApplication(argc, argv)
{
    m_prompt = new Prompt(globalContext);
}

bool App::init()
{
    return true;
}

bool App::start()
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

Context* App::context()
{
    return globalContext;;
}
