#ifndef INSERT_H
#define INSERT_H

#include "../command.h"

#include <QDebug>

class Insert : public Command
{
    Q_OBJECT
public:
    explicit Insert(QObject *parent = nullptr);
    explicit Insert(QString argument,  QObject *parent = nullptr);

    bool execute() const override;
};

#endif // INSERT_H
