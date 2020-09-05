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

    static const QString STORE;
    static const QString SLICE;


private:
    bool createStore(const QString &store) const;
    bool createStores(const QList<QString> &stores) const;

    bool createSlice(const QString &store, const QString &slice) const;
    bool createSlices(const QString &store, const QList<QString> &slices) const;
};

#endif // CREATECOMMAND_H
