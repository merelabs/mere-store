#ifndef MERESTORECOMMAND_H
#define MERESTORECOMMAND_H

#include <QObject>

class MereStoreCommand : public QObject
{
public:
    explicit MereStoreCommand(QObject *parent = 0);

    virtual bool execute() const = 0;
};

#endif // MERESTORECOMMAND_H
