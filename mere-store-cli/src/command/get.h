#ifndef GET_H
#define GET_H

#include "command.h"

class Get : public Command
{
    Q_OBJECT
public:
    explicit Get(QObject *parent = nullptr);
    explicit Get(QString argument,  QObject *parent = nullptr);

    void setArgument(QString argument);

    bool execute() const override;
};

#endif // GET_H
