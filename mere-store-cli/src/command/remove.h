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
    void help() const override;

private:
    bool removeStore(const QString &store) const;
    bool removeSlice(const QString &slice) const;

};

#endif // REMOVE_H
