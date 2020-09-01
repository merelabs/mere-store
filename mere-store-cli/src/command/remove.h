#ifndef REMOVE_H
#define REMOVE_H

#include "command.h"

class Remove : public Command
{
    Q_OBJECT
public:
    explicit Remove(QObject *parent = nullptr);
    explicit Remove(QString argument,  QObject *parent = nullptr);

    void setArgument(QString argument);

    QString subject() const;
    QString object() const;

    bool execute() const override;
};

#endif // REMOVE_H
