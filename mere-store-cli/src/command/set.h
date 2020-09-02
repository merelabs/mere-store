#ifndef SET_H
#define SET_H

#include "../command.h"

class Set : public Command
{
    Q_OBJECT
public:
    explicit Set(QObject *parent = nullptr);
    explicit Set(QString argument,  QObject *parent = nullptr);

    bool execute() const override;
    void help() const override;
};

#endif // SET_H
