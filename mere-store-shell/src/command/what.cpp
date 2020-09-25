#include "what.h"

What::What(QObject *parent)
    : What("", parent)
{

}

What::What(QString argument, QObject *parent)
    : Command(Command::What, argument, parent)
{

}

bool What::execute() const
{
    //qDebug() << "Going to run " << this->command() << " with the arguments " << this->argument();

    bool ok = true;

    QTextStream(stdout) << "So, you want to know all about KKKKDB?" << Qt::endl
                        << "Ok, it is a simple, small, fast storage system primarily focus on embedded use," << Qt::endl
                        << "but not limited to that worth to mentioned" << Qt::endl
                        ;

    return ok;
}
