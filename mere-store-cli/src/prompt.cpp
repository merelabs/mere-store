#include "prompt.h"
#include "context.h"

Prompt::Prompt(Context *context, QObject *parent)
    : QObject(parent),
      m_input(stdin),
      m_context(context)
{

}

void Prompt::welcome() const
{
    qDebug() << "Welcome to SliceDB v1.0.0";
}

QString Prompt::accept()
{
    QTextStream(stdout) << QString("%1>").arg(m_context->get());

    return m_input.readLine();
}
