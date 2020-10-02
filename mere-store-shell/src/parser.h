#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QStringRef>
#include <QStringList>

#include <QDebug>

class Parser
{
public:
    explicit Parser(const QString &arguments, const QStringList options = QStringList(""));

    QStringRef next();
    QStringRef rest();

    bool isOption();
    bool isOption(const QString option);

private:
    int m_position;
    QStringRef m_argument;

    const QString &m_arguments;
    const QStringList m_options;
};

#endif // PARSER_H
