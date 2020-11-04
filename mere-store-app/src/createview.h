#ifndef CREATEVIEW_H
#define CREATEVIEW_H

#include <QLineEdit>
#include <QWidget>
#include <QDebug>

class CreateView : public QWidget
{
    Q_OBJECT
public:
    ~CreateView();
    explicit CreateView(QWidget *parent = nullptr);


protected:
    void showEvent(QShowEvent *event) override;

private:
    void initUI();
    void initHeaderUI();

signals:
    void created();
    void cancelled();

private slots:
    void create();

private:
    QLineEdit *m_name;
};

#endif // CREATEVIEW_H
