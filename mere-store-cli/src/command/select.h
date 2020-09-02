#ifndef OPEN_H
#define OPEN_H

#include "../command.h"

class Select : public Command
{
    Q_OBJECT
public:
    explicit Select(QObject *parent = nullptr);
    explicit Select(QString argument,  QObject *parent = nullptr);

    bool execute() const override;
    void help() const override;

private:
    bool selectStore(const QString &store) const;
    bool selectSlice(const QString &slice) const;

signals:
    void selected(QString) const;
};

#endif // OPEN_H
