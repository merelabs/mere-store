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
    explicit CreateView(const QString *store = nullptr, QWidget *parent = nullptr);

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
    const QString *m_store;

    QLineEdit *m_name;
};

#endif // CREATEVIEW_H
