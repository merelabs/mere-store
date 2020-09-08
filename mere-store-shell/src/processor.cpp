#include "processor.h"

Processor::~Processor()
{

}

Processor::Processor(const QString &input, QObject *parent)
    : QObject(parent),
      m_input(input)
{

}

QString Processor::input() const
{
    return m_input;
}
