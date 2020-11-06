#ifndef KEYLISTVIEW_H
#define KEYLISTVIEW_H

#include <QWidget>
#include <QDebug>

class PkgListView : public QWidget
{
    Q_OBJECT
public:
    ~PkgListView();
    explicit PkgListView(QWidget *parent = nullptr);

signals:

};

#endif // KEYLISTVIEW_H
