#include "processor.h"

Processor::Processor(const QString &input, QObject *parent)
    : QObject(parent),
      m_input(input)
{

}

const QString Processor::input() const
{
    return m_input;
}
