#ifndef KVUTILS_H
#define KVUTILS_H

#include <QMap>
#include <QString>
#include <QDebug>

/*
 * The formal definition of key-value pairs that we support as follows:
 * pairs  = <key>[delim]<value>([delim]<key>[delim]<value>)*
 * pair   = <key>[delim]<value>
 * key    = <string>|<quoter><string><quoter>
 * value  = <string>|<quoter><string><quoter>
 * quoter = '|"
 * delim  = BLANKSPACE
*/

class KVUtils
{
public:
    static QList<QPair<QString, QString> > split(const QString &input, const QString &delim = " ");
    static QList<QString> blocks(const QString &input, const QString &delim = " ");

private:
    static QString key(QString &input);
    static QString value(QString &input);

    static QString block(QString &input);
    static QString quotedBlock(QString &input);
    static QString simpleBlock(QString &input);
};

#endif // KVUTILS_H
