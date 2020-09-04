#include "context.h"

const QString Context::Root  = ".";
const QString Context::Store = "store";
const QString Context::Slice = "slice";

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

void Context::selected(QString store)
{
    m_store = store;
}

void Context::selected(QString context, QString value)
{
    if (context.compare(Context::Store) == 0)
        m_store = value;
    else if (context.compare(Context::Slice) == 0)
        m_slice = value;
}
