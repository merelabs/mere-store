#include "history.h"
#include "../kvutils.h"

#include "mere/utils/merestringutils.h"

#include <QListIterator>

QList<QString> History::m_history;

History::History(QObject *parent)
    : History("", parent)
{

}

History::History(QString argument, QObject *parent)
    : Command(Command::History, argument, parent)
{

}

bool History::execute() const
{
    //qDebug() << "Going to run " << this->command() << " with the arguments " << this->argument();

    bool ok = true;

    QList<QString> blocks;

    try
    {
        blocks = KVUtils::blocks(this->argument());
    }
    catch (...)
    {
        qDebug() << "Exception....";
    }

    QTextStream out(stdout);

    QListIterator<QString> it(History::m_history);
    while (it.hasNext())
    {
        out << "- " << it.next() << endl;
    }

    return ok;
}

//static
bool History::append(const QString &history)
{
    bool ok = false;

    if ((ok = !MereStringUtils::isBlank(history)))
        m_history.append(history);

    return ok;
}
