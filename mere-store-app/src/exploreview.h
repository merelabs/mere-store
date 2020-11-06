#ifndef EXPLOREVIEW_H
#define EXPLOREVIEW_H

#include <QWidget>

class SearchView;
class PkgListView;
class DetailView;
class ExploreView : public QWidget
{
    Q_OBJECT
public:
    ~ExploreView();
    explicit ExploreView(QWidget *parent = nullptr);

    void setStore(const QString &store);

private:
    void initUI();

signals:

private:
    SearchView *m_seachView;
    PkgListView *m_listView;
    DetailView *m_detailView;
};

#endif // EXPLOREVIEW_H
