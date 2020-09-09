#ifndef WHAT_H
#define WHAT_H

#include "../command.h"

class What : public Command
{
    Q_OBJECT
public:
    explicit What(QObject *parent = nullptr);
    explicit What(QString argument,  QObject *parent = nullptr);

    bool execute() const override;
};

#endif // WHAT_H
