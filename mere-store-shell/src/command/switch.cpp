#include "switch.h"
#include "../shell.h"
#include "../context.h"

Switch::Switch(QObject *parent)
    : Switch("", parent)
{

}

Switch::Switch(QString argument, QObject *parent)
    : Command(Command::Switch, argument, parent)
{
    connect(this, SIGNAL(switched(const QString&)), Shell::context(), SLOT(switched(const QString&)));
}

bool Switch::execute() const
{
    //qDebug() << "Going to run " << this->command() << " with the arguments " << this->argument();
    bool ok = false;

    return ok;
}
