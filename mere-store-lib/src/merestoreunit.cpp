#include "merestoreunit.h"

class MereStoreUnit::MereStoreUnitPrivate
{
public:
    ~MereStoreUnitPrivate()
    {

    }

    MereStoreUnitPrivate(MereStoreUnit *q)
        :q_ptr(q)
    {

    }

    MereStoreUnitAttributes attributes() const
    {
        return m_attributes;
    }

    void setAttributes(MereStoreUnitAttributes attributes)
    {
        m_attributes = attributes;
    }

    void addAttribute(const QString &name, const QVariant &value)
    {
        m_attributes.insert(name, value);
    }

    void addAttributes(MereStoreUnitAttributes attributes)
    {
        QMapIterator<QString, QVariant> it(attributes);
        while (it.hasNext())
        {
            it.next();
            addAttribute(it.key(), it.value());
        }
    }

private:
    MereStoreUnitAttributes m_attributes;

    MereStoreUnit *q_ptr;
};


MereStoreUnit::~MereStoreUnit()
{
    delete d_ptr;
}

MereStoreUnit::MereStoreUnit(const QString &type)
    : d_ptr(new MereStoreUnitPrivate(this))
{
    setType(type);
}

MereStoreUnitAttributes MereStoreUnit::attributes() const
{
    return d_ptr->attributes();
}

void MereStoreUnit::setAttributes(MereStoreUnitAttributes attributes)
{
    d_ptr->setAttributes(attributes);
}

void MereStoreUnit::addAttribute(const QString &name, const QVariant &value)
{
    return d_ptr->addAttribute(name, value);
}

void MereStoreUnit::addAttributes(MereStoreUnitAttributes attributes)
{
    return d_ptr->addAttributes(attributes);
}

MereStoreUnitMap MereStoreUnit::map() const
{
    MereStoreUnitMap unit;

    unit.insert("path", path());
    unit.insert("type", type());
    unit.insert("uuid", uuid());
    unit.insert("attr", attributes());

    return unit;
}
