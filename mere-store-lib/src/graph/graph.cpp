#include "graph.h"

class Mere::Store::Graph::GraphPrivate
{
public:
    ~GraphPrivate()
    {
    }

    GraphPrivate(Graph *q)
        : q_ptr(q)
    {
        Q_UNUSED(q_ptr)
    }

    QString name() const
    {
        return m_name;
    }

    void setName(const QString &name)
    {
        m_name = name;
    }

private:
    QString m_name;

    Graph *q_ptr;
};

Mere::Store::Graph::~Graph()
{

}

Mere::Store::Graph::Graph()
{

}

Mere::Store::Graph::Graph(const QString &name)
    : d_ptr(new GraphPrivate(this))
{

}

QString Mere::Store::Graph::name() const
{
    return d_ptr->name();
}

void Mere::Store::Graph::setName(const QString &name)
{
    return d_ptr->setName(name);
}
