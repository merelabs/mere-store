#ifndef SEARCHVIEW_H
#define SEARCHVIEW_H

#include <QLineEdit>
#include <QWidget>
#include <QDebug>

class SearchView : public QWidget
{
    Q_OBJECT
public:
    ~SearchView();
    explicit SearchView(QWidget *parent = nullptr);

private:
    void initUI();

signals:

private slots:
    void search();

private:
    QLineEdit *m_searchText;
};

#endif // SEARCHVIEW_H
