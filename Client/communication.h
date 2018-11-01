#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QString>

class Communication : public QWidget
{
    Q_OBJECT
public:
    explicit Communication(QString name,QWidget *parent = nullptr);
    ~Communication();
    QString gettext();
    void settext(QString text);
    void clean();
private:
    QLabel *l_name;
    QTextEdit *t_recv;
    QTextEdit *t_send;
    QPushButton *b_send;
    QPushButton *b_return;
    QPushButton *b_exit;


signals:
    void send();
    void return_widget();
    void quit();

public slots:
};

#endif // COMMUNICATION_H
