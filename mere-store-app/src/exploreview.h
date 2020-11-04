#ifndef EXPLOREVIEW_H
#define EXPLOREVIEW_H

#include <QWidget>

class SearchView;
class ListView;
class DetailView;
class ExploreView : public QWidget
{
    Q_OBJECT
public:
    ~ExploreView();
    explicit ExploreView(QWidget *parent = nullptr);

private:
    void initUI();

signals:

private:
    SearchView *m_seachView;
    ListView *m_listView;
    DetailView *m_detailView;
};

#endif // EXPLOREVIEW_H
