#ifndef REMOVE_H
#define REMOVE_H

#include "../command.h"

class Remove : public Command
{
    Q_OBJECT
public:
    explicit Remove(QObject *parent = nullptr);
    explicit Remove(QString argument,  QObject *parent = nullptr);

    bool execute() const override;

private:
    bool removeStore(const QString &store) const;
    bool removeStores(const QList<QString> &stores) const;

    bool removeSlice(const QString &store, const QString &slice) const;
    bool removeSlices(const QString &store, const QList<QString> &slices) const;
};

#endif // REMOVE_H
