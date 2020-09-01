#ifndef CONFIG_H
#define CONFIG_H

#include "command.h"

class Config : public Command
{
    Q_OBJECT
public:
    explicit Config(QObject *parent = nullptr);
    explicit Config(QString argument,  QObject *parent = nullptr);

    void setArgument(QString argument);

    QString subject() const;
    QString object() const;

    bool execute() const override;
};

#endif // CONFIG_H
