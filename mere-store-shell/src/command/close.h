#ifndef CLOSE_H
#define CLOSE_H

#include "../command.h"

class Close : public Command
{
    Q_OBJECT
public:
    explicit Close(QObject *parent = nullptr);
    explicit Close(QString argument,  QObject *parent = nullptr);

    //void setArgument(QString argument);

    QString subject() const;
    QString object() const;

    bool execute() const override;
    void help() const override;
};

#endif // CLOSE_H
