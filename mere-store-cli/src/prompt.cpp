#include "prompt.h"
#include "context.h"

Prompt::Prompt(Context *context, QObject *parent)
    : QObject(parent),
      m_input(stdin),
      m_context(context)
{

}

QString Prompt::accept()
{
    qDebug() << "YYYY>>>>>>>>>>>>" << m_context << m_context->get();

    QTextStream(stdout) << QString("%1>").arg(m_context->get());

    return m_input.readLine();
}
