#ifndef CREATECOMMAND_H
#define CREATECOMMAND_H

#include "command.h"

class Store;
class Type;

class Create : public Command
{
    Q_OBJECT
public:
    explicit Create(QObject *parent = nullptr);
    explicit Create(QString argument,  QObject *parent = nullptr);

    void setArgument(QString argument);

    QString subject() const;
    QString object() const;

    bool execute() const override;

private:
    Store *m_store;
    Type  *m_type;
};

#endif // CREATECOMMAND_H
