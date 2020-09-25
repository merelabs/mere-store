#ifndef MERESTOREENGINE_H
#define MERESTOREENGINE_H

#include <QObject>

namespace Mere
{
namespace Store
{

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = nullptr);

    //virtual void init() = 0;
    virtual int create() = 0;
    virtual int open() = 0;
    virtual int close() = 0;
    virtual int remove() = 0;
    virtual bool exists() = 0;

signals:
    void created();
    void opened();
    void closed();
    void removed();
};

} // namespace Store
} // namespace Mere

#endif // MERESTOREENGINE_H
