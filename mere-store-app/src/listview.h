#ifndef KEYLISTVIEW_H
#define KEYLISTVIEW_H

#include <QWidget>
#include <QDebug>

class ListView : public QWidget
{
    Q_OBJECT
public:
    ~ListView();
    explicit ListView(QWidget *parent = nullptr);

signals:

};

#endif // KEYLISTVIEW_H
