#ifndef HISTORY_H
#define HISTORY_H

#include "../command.h"

#include <QList>

class History : public Command
{
    Q_OBJECT
public:
    explicit History(QObject *parent = nullptr);
    explicit History(QString argument,  QObject *parent = nullptr);

    bool execute() const override;

    static bool append(const QString &history);

private:
    static QList<QString> m_history;
};

#endif // HISTORY_H
