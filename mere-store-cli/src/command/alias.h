#ifndef ALIAS_H
#define ALIAS_H

#include "../command.h"

class Alias : public Command
{
    Q_OBJECT
public:
    explicit Alias(QObject *parent = nullptr);
    explicit Alias(QString argument,  QObject *parent = nullptr);

    bool execute() const override;

    static bool has(const QString &key);
    static QString alias(const QString &key);


    void help() const override;

    void show() const;
    void show(const QString &alias) const;
    void add(const QString &alias, const QString &command) const;

private:
    static QHash<QString, QString> m_commands;

};

#endif // ALIAS_H
