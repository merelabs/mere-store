#ifndef MERESTORELISTCOMMAND_H
#define MERESTORELISTCOMMAND_H

#include "../command.h"

class List : public Command
{
    Q_OBJECT
public:
    explicit List(QObject *parent = nullptr);
    explicit List(QString argument, QObject *parent = nullptr);

    bool execute() const override;
    void help() const override;
};

#endif // MERESTORELISTCOMMAND_H
