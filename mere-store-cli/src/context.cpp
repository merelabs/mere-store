#include "context.h"

const QString Root  = ".";
const QString Store = "store";
const QString Slice = "slice";

Context::Context(QObject *parent)
    : QObject(parent),
      m_context("")
{

}

QString Context::get() const
{
    return m_context;
}

void Context::selected(QString context)
{
    m_context = context;
}
