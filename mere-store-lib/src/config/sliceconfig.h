#ifndef SLICECONFIG_H
#define SLICECONFIG_H

#include <QObject>
#include <QVariant>

class SliceConfig
{
public:
    explicit SliceConfig();

signals:

private:
    QMap<QString, QVariant> m_config;
};

#endif // SLICECONFIG_H
