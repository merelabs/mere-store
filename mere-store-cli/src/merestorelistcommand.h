#ifndef MERESTORELISTCOMMAND_H
#define MERESTORELISTCOMMAND_H

#include "merestorecommand.h"

class MereStoreListCommand : public MereStoreCommand
{
    Q_OBJECT
public:
    explicit MereStoreListCommand(QObject *parent = nullptr);

    bool execute() const override;
signals:

public slots:
};

#endif // MERESTORELISTCOMMAND_H
