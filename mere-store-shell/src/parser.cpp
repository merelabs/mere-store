#include "parser.h"

Parser::Parser(const QString &arguments, const QStringList options)
    : m_position(-1),
      m_arguments(arguments),
      m_options(options)
{
}

QStringRef Parser::next()
{
    if (m_arguments.size() == m_position)
        return 0;

    QStringRef ref;

    int pos = m_arguments.indexOf(" ", m_position + 1);
    if (pos == -1)
        pos = m_arguments.size();

    ref = m_arguments.midRef(m_position + 1, pos - m_position - 1);
    m_argument = ref;
    m_position = pos;

    if (ref.size() == 0)
        return next();

    return ref;
}

QStringRef Parser::rest()
{
    m_argument = m_arguments.midRef(m_position + 1);
    m_position = m_arguments.size();

    return m_argument;
}

bool Parser::isOption()
{
    return m_options.contains(m_argument);
}

bool Parser::isOption(const QString option)
{
    return m_argument.compare(option) == 0;
}
