#ifndef OPEN_H
#define OPEN_H

#include "command.h"

class Select : public Command
{
    Q_OBJECT
public:
    explicit Select(QObject *parent = nullptr);
    explicit Select(QString argument,  QObject *parent = nullptr);

    void setArgument(QString argument);

    QString subject() const;
    QString object() const;

    bool execute() const;

signals:
    void selected(QString) const;
};

#endif // OPEN_H
