#ifndef SET_H
#define SET_H

#include "../command.h"

class Set : public Command
{
    Q_OBJECT
public:
    explicit Set(QObject *parent = nullptr);
    explicit Set(QString argument,  QObject *parent = nullptr);

    bool execute() const override;

private:
    QString type(const QString &option) const;

    bool set(const QString &key, const QString &value, const QString &type) const;
    bool setStore(const QString &key, const QString &value, const QString &type) const;
    bool setSlice(const QString &key, const QString &value, const QString &type) const;
};

#endif // SET_H
