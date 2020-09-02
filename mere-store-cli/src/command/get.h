#ifndef GET_H
#define GET_H

#include "../command.h"

class Get : public Command
{
    Q_OBJECT
public:
    explicit Get(QObject *parent = nullptr);
    explicit Get(QString argument,  QObject *parent = nullptr);

    bool execute() const override;
    void help() const override;
};

#endif // GET_H
