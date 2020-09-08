#ifndef PROMPT_H
#define PROMPT_H

#include <QObject>
#include <QTextStream>

class Context;

class Prompt : public QObject
{
    Q_OBJECT
public:
    explicit Prompt(Context *context, QObject *parent = nullptr);

    QString accept();
    void welcome() const;

signals:

private:
    QTextStream m_input;

    Context *m_context;
};

#endif // PROMPT_H
