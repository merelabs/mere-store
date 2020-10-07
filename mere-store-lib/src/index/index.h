#ifndef INDEX_H
#define INDEX_H

#include <QList>
#include <QString>

namespace Mere
{
namespace Store
{

class Index
{
public:
    explicit Index();
    explicit Index(const QString &name);

    QString name() const;
    void setName(const QString &name);

    QList<QString> attributes() const;
    void addAttribute(const QString &attribute);
    void addAttributes(const QList<QString> &attributes);

    void setAttribute(const QString &attribute);
    void setAttributes(const QList<QString> &attributes);

    bool unique() const;
    void setUnique(const bool &unique);

private:
    class IndexPrivate;
    IndexPrivate *d_ptr;
};

} // namespace Store
} // namespace Mere

#endif // INDEX_H
