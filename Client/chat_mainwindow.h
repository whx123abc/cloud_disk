#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "chatmessage/qnchatmessage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString user_name, QWidget *parent = 0);
    ~MainWindow();

    void dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QNChatMessage::User_Type type);
    void dealMessageTime(QString curMsgTime);
    void showMsg(QString msg);
    QString getCurUser();
protected:
    void resizeEvent(QResizeEvent *event);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
signals:
    void open_chat(QString username);
    void send_msg(QString msg);
    void close_cur_w();

private:
    Ui::MainWindow *ui;
    //Widget *main_w;
    QString cur_user;
};

#endif // MAINWINDOW_H
