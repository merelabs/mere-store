#ifndef VOID_H
#define VOID_H

#include "../command.h"

#include <QDebug>

class Void : public Command
{
    Q_OBJECT
public:
    explicit Void(QObject *parent = nullptr);
    explicit Void(QString argument,  QObject *parent = nullptr);

    bool execute() const override;
};

#endif // VOID_H
