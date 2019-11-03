#ifndef MEREDEFAULTSTORE_H
#define MEREDEFAULTSTORE_H

#include "merestoreglobal.h"
#include "merestore.h"

#include <QObject>

class MERE_STORE_LIBSPEC MereDefaultStore : public MereStore
{
    Q_OBJECT
public:
    virtual ~MereDefaultStore();
    explicit MereDefaultStore(const QString store, QObject *parent = nullptr);

    virtual void save(T unit);
    virtual void create(T unit);
    virtual void update(T unit);
    virtual void fetch(T unit);
    virtual void remove(T unit);

    virtual void search(T query);

protected:
    static QString UNIT_KEY;
    static QString UNIT_ATTR_KEY;

private:
    int read(const QString pkey, T &data);
    int write(const QString unit, const QUuid uuid, const T data);
    int remove(const QString pkey);

signals:

public slots:
};

#endif // MEREDEFAULTSTORE_H
