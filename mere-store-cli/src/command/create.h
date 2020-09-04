#ifndef CREATECOMMAND_H
#define CREATECOMMAND_H

#include "../command.h"

class Store;
class Type;

class Create : public Command
{
    Q_OBJECT
public:
    explicit Create(QObject *parent = nullptr);
    explicit Create(QString argument,  QObject *parent = nullptr);

    bool execute() const override;

private:
    bool createStore(const QString &store) const;
    bool createSlice(const QString &store, const QString &slice) const;
};

#endif // CREATECOMMAND_H
