#ifndef HELP_H
#define HELP_H

#include "../command.h"

class Help : public Command
{
    Q_OBJECT
public:
    explicit Help(QObject *parent = nullptr);
    explicit Help(QString argument,  QObject *parent = nullptr);

    bool execute() const override;
};

#endif // HELP_H
