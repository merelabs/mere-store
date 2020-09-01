#ifndef MERESTORECOMMAND_H
#define MERESTORECOMMAND_H

#include <QObject>
#include <QHash>
#include <QDebug>

class Context;

class Command : public QObject
{
public:
    explicit Command(QString command, QString argument, QObject *parent = 0);

    virtual bool execute() const = 0;

    QString command() const;
    QString argument() const;
    void setArgument(const QString argument);

    static Command* get(const QString &key);

    static const QString Close;
    static const QString Config;
    static const QString Create;
    static const QString Del;
    static const QString Exit;
    static const QString Get;
    static const QString Insert;
    static const QString List;
    static const QString Quit;
    static const QString Remove;
    static const QString Select;
    static const QString Set;
    static const QString Void;

private:
    QString m_command;
    QString m_argument;

    static QHash<QString, Command *> m_commands;
};

#endif // MERESTORECOMMAND_H
