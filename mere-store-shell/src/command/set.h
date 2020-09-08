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
    QString key() const;
    QString value() const;

    bool set(const QString &key, const QString &value) const;
    bool setStore(const QString &key, const QString &val) const;
    bool setSlice(const QString &key, const QString &val) const;
};

#endif // SET_H
