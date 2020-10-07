#ifndef GRAPH_H
#define GRAPH_H

#include <QString>

namespace Mere
{
namespace Store
{

class Graph
{
public:
    virtual ~Graph();
    explicit Graph();
    explicit Graph(const QString &graph);

    QString name() const;
    void setName(const QString &name);

private:
    class GraphPrivate;
    GraphPrivate *d_ptr;
};

} // namespace Store
} // namespace Mere

#endif // GRAPH_H
