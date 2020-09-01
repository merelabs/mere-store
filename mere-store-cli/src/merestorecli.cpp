#include "merestorecli.h"

#include "input.h"
#include "prompt.h"
#include "context.h"
#include "command.h"

Q_GLOBAL_STATIC(Context, globalContext)

MereCli::MereCli(int argc, char *argv[])
    : QCoreApplication(argc, argv)
{
    //installEventFilter(this);

    m_prompt = new Prompt(globalContext);
}

//bool MereCli::eventFilter(QObject */*object*/, QEvent */*event*/)
//{
////    if (event->type() == QEvent::KeyPress) {
////        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
////        voxity::RegisterKeydown(QtKeyToSFML(keyEvent->key()));

////        return true;
////    }

////    if (event->type() == QEvent::KeyRelease) {
////        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
////        voxity::RegisterKeyup(QtKeyToSFML(keyEvent->key()));
////        return true;
////    }

////    if(event->type() == QEvent::Shortcut){
////        QShortcutEvent *sc = static_cast<QShortcutEvent *>(event);
////        const QKeySequence &ks = sc->key();

////        voxity::RegisterKeydown(QtKeyToSFML(sc->key()[0]));
////        return true;
////    }

//    return true;
//}

bool MereCli::init()
{
    return true;
}

bool MereCli::start()
{
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

Context* MereCli::context()
{
    return globalContext;;
}
