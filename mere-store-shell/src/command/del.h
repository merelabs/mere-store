#ifndef DEL_H
#define DEL_H

#include "../command.h"

class Del : public Command
{
    Q_OBJECT
public:
    explicit Del(QObject *parent = nullptr);
    explicit Del(QString argument,  QObject *parent = nullptr);

    bool execute() const override;

private:
    bool del(const QString &key) const;
    bool delStore(const QString &key) const;
    bool delSlice(const QString &key) const;

    bool del(const QList<QString> &keys) const;
    bool delStore(const QList<QString> &keys) const;
    bool delSlice(const QList<QString> &keys) const;
};

#endif // DEL_H
