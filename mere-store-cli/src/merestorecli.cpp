#include "merestorecli.h"

#include "mere/store/meredefaultstore.h"

#include <QMap>
#include <QTextStream>

MereCli::MereCli(int argc, char *argv[])
    : QCoreApplication(argc, argv)
{
    installEventFilter(this);
}

bool MereCli::eventFilter(QObject */*object*/, QEvent *event)
{
qDebug() << "SO WHAT?";
//    if (event->type() == QEvent::KeyPress) {
//        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
//        voxity::RegisterKeydown(QtKeyToSFML(keyEvent->key()));

//        return true;
//    }

//    if (event->type() == QEvent::KeyRelease) {
//        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
//        voxity::RegisterKeyup(QtKeyToSFML(keyEvent->key()));
//        return true;
//    }

//    if(event->type() == QEvent::Shortcut){
//        QShortcutEvent *sc = static_cast<QShortcutEvent *>(event);
//        const QKeySequence &ks = sc->key();

//        voxity::RegisterKeydown(QtKeyToSFML(sc->key()[0]));
//        return true;
//    }

    return true;
}
bool MereCli::init()
{
    return true;
}

bool MereCli::start()
{
    QTextStream input(stdin);

    QString line;
    do
    {
        QTextStream(stdout)  << ">";
        line = input.readLine();

        qDebug() << "Executing command: " << line;

        if (line.compare("list") == 0)
        {
            MereDefaultStore store("/home/iklash/.mere/board/boarddb");
            store.init();
            QMap<QString, QVariant> map;
            store.list(map);
        }

    } while (line.compare("exit") && line.compare("quit"));

    ::exit(0);

    return true;
}
