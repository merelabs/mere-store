#ifndef MERESTOREUNITDESCRIPTOR_H
#define MERESTOREUNITDESCRIPTOR_H

#include <QUuid>
#include <QString>
#include <QVariant>
#include <QDateTime>

class UnitDescriptor
{
public:
    virtual ~UnitDescriptor();
    UnitDescriptor();

    QUuid uuid() const;
    void setUuid(QUuid uuid);

    QString type() const;
    void setType(QString type);

    QString path() const;
    void setPath(QString path);

    QString createdBy() const;
    void setCreatedBy(const QString &by);

    QDateTime createdAt() const;
    void setCreatedAt(const QDateTime &datetime);

    QString updatedBy() const;
    void setUpdatedBy(const QString &by);

    QDateTime updatedAt() const;
    void setUpdatedAt(const QDateTime &datetime);

    QMap<QString, QVariant> map() const;

private:
    QUuid     m_uuid;
    QString   m_type;
    QString   m_path;

    QString   m_createdBy;
    QDateTime m_createdAt;

    QString   m_updatedBy;
    QDateTime m_updatedAt;
};

#endif // MERESTOREUNITDESCRIPTOR_H
