#ifndef CONFIG_H
#define CONFIG_H

#include "../command.h"

class Config : public Command
{
    Q_OBJECT
public:
    explicit Config(QObject *parent = nullptr);
    explicit Config(QString argument,  QObject *parent = nullptr);

    bool execute() const override;

    QString key() const;
    QString value() const;
};

#endif // CONFIG_H
