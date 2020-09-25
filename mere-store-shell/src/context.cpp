#include "context.h"

#include "mere/store/store.h"

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
