#ifndef MSET_H
#define MSET_H

#include "../command.h"

class MSet : public Command
{
    Q_OBJECT
public:
    explicit MSet(QObject *parent = nullptr);
    explicit MSet(QString argument,  QObject *parent = nullptr);

    bool execute() const override;
    void help() const override;
};

#endif // MSET_H
