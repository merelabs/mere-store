#ifndef CONNECTVIEW_H
#define CONNECTVIEW_H

#include <QLineEdit>
#include <QWidget>
#include <QDebug>

class SelectView : public QWidget
{
    Q_OBJECT
public:
    explicit SelectView(QWidget *parent = nullptr);

protected:
    void showEvent(QShowEvent *event) override;

private:
    void initUI();
    void initHeaderUI();

signals:
    void selected();
    void cancelled();

private slots:
    void select();

private:
    QLineEdit *m_name;
};

#endif // CONNECTVIEW_H
