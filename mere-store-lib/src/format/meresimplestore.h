#ifndef MERESIMPLE_H
#define MERESIMPLE_H

#include "../merestoreglobal.h"
#include "../mereabstractstore.h"
#include "../merestoreunit.h"
#include "../engine/merestoreengine.h"

#include <QObject>

class MereSimpleStore : public MereAbstractStore
{
    Q_OBJECT
public:
    virtual ~MereSimpleStore();
    explicit MereSimpleStore(const QString store, QObject *parent = nullptr);

    virtual int set(QVariant value);
    virtual int set(const QString key, QVariant value);

    virtual QVariant get(const QString &key);
    virtual QVariant del(const QString &key);

    virtual QVariant list() override;

signals:

};

#endif // MERESIMPLE_H
