#ifndef INSERT_H
#define INSERT_H

#include "command.h"

#include <QDebug>

class Insert : public Command
{
    Q_OBJECT
public:
    explicit Insert(QObject *parent = nullptr);
    explicit Insert(QString argument,  QObject *parent = nullptr);

    void setArgument(QString argument);

    QString subject() const;
    QString object() const;

    bool execute() const override;
signals:

};

#endif // INSERT_H
