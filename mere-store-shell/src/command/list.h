#ifndef MERESTORELISTCOMMAND_H
#define MERESTORELISTCOMMAND_H

#include "../command.h"

class List : public Command
{
    Q_OBJECT
public:
    explicit List(QObject *parent = nullptr);
    explicit List(QString argument, QObject *parent = nullptr);

    bool execute() const override;

private:
    QVariant list() const;
    QVariant list(const uint &limit) const;
    QVariant list(const QString &key) const;
    QVariant list(const QString &key, const uint &limit) const;
};

#endif // MERESTORELISTCOMMAND_H
