#ifndef GET_H
#define GET_H

#include "../command.h"

class Get : public Command
{
    Q_OBJECT
public:
    explicit Get(QObject *parent = nullptr);
    explicit Get(QString argument,  QObject *parent = nullptr);

    bool execute() const override;

private:
    QVariant get(const QString &key) const;
    QVariant getStore(const QString &key) const;
    QVariant getSlice(const QString &key) const;
};

#endif // GET_H
