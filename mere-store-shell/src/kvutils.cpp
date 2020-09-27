#include "kvutils.h"

#include "mere/utils/merestringutils.h"

QList<QPair<QString, QString>> KVUtils::pairs(const QString &input, const QString &delim)
{
    QList<QPair<QString, QString>> pairs;

    QString local = input.trimmed();
    while (local.length())
    {
        QString key   = KVUtils::key(local);
        QString value = KVUtils::value(local);

        QPair<QString, QString> pair(key, value);
        pairs.append(pair);
    }

    return pairs;
}

QList<QString> KVUtils::blocks(const QString &input, const QString &delim)
{
    QList<QString> blocks;

    QString local = input.trimmed();
    while (local.length())
    {
        QString block = KVUtils::block(local);

        blocks.append(block);
    }

    return blocks;
}

QString KVUtils::key(QString &input)
{
    return KVUtils::block(input);
}

QString KVUtils::value(QString &input)
{
    return KVUtils::block(input);
}

QString KVUtils::block(QString &input)
{
    QString block;

    if (input.at(0) == '"')
        block = KVUtils::quotedBlock(input);
    else
        block = KVUtils::simpleBlock(input);

    return block;;
}

QString KVUtils::quotedBlock(QString &input)
{
    QString block;

    int pos = 0;
    int len = 0;

    do
    {
        pos = input.indexOf("\"", pos + 1);
        if (pos == -1)
            throw "ERROR: Closing quoter is not found.";
    }
    while (input.at(pos - 1) == '\\');

    block = input.mid(1, pos-1);

    len = pos + 1;

    input.remove(0, len);

    return block;
}

QString KVUtils::simpleBlock(QString &input)
{
    QString block;

    int pos = -1;
    int len = 0;

    pos = input.indexOf(" ");
    if (pos != -1)
    {
        block = input.left(pos);
        len = pos + 1;
    }
    else
    {
        block = input.left(input.length());
        len = input.length();
    }

    input.remove(0, len);

    return block;
}
