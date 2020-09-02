#ifndef DEL_H
#define DEL_H

#include "../command.h"

class Del : public Command
{
    Q_OBJECT
public:
    explicit Del(QObject *parent = nullptr);
    explicit Del(QString argument,  QObject *parent = nullptr);

    bool execute() const override;
    void help() const override;
};

#endif // DEL_H
