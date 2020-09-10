#ifndef SWITCH_H
#define SWITCH_H

#include "../command.h"

class Switch : public Command
{
    Q_OBJECT
public:
    explicit Switch(QObject *parent = nullptr);
    explicit Switch(QString argument,  QObject *parent = nullptr);

    bool execute() const override;

signals:
    void switched(const QString&);
};

#endif // SWITCH_H
