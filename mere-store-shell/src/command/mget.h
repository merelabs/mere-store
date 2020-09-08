#ifndef MGET_H
#define MGET_H

#include "../command.h"

class MGet : public Command
{
    Q_OBJECT
public:
    explicit MGet(QObject *parent = nullptr);
    explicit MGet(QString argument,  QObject *parent = nullptr);

    bool execute() const override;
};

#endif // MGET_H
