#ifndef STOREPANEL_H
#define STOREPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QDebug>

class CreateView;
class SelectView;

class StorePanel : public QWidget
{
    Q_OBJECT
public:
    ~StorePanel();
    explicit StorePanel(QWidget *parent = nullptr);

private:
    void initUI();
    QPushButton *addControl(const QIcon &icon);

signals:
    void selected(const QString &store);

private slots:
    void select();
    void create();

private:
    SelectView *m_selectView;
    CreateView *m_createView;
};

#endif // STOREPANEL_H
