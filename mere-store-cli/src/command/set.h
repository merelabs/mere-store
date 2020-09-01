#ifndef SET_H
#define SET_H

#include "command.h"

class Set : public Command
{
    Q_OBJECT
public:
    explicit Set(QObject *parent = nullptr);
    explicit Set(QString argument,  QObject *parent = nullptr);

    void setArgument(QString argument);

    bool execute() const override;
};

#endif // SET_H
