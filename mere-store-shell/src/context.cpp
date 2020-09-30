#include "context.h"

#include "mere/store/store/store.h"
#include "mere/utils/merestringutils.h"

Context::Context(QObject *parent)
    : QObject(parent),
      m_store(""),
      m_slice("")
{

}

QString Context::store() const
{
    return m_store;
}

QString Context::slice() const
{
    return m_slice;
}

QString Context::context() const
{
    QString context = "root";

    if (MereStringUtils::isNotBlank(m_slice))
        context = Mere::Store::Type::SLICE;
    else if (MereStringUtils::isNotBlank(m_store))
        context = Mere::Store::Type::STORE;

    return context;
}

void Context::switched(const QString &value)
{

}

void Context::selected(const QString &context, const QString &value)
{
    if (Mere::Store::Type::STORE.compare(context) == 0)
    {
        m_store = value;
        m_slice = "";
    }
    else if (Mere::Store::Type::SLICE.compare(context) == 0)
    {
        m_slice = value;
    }
}
