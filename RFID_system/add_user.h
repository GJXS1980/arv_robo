#ifndef ADD_USER_H
#define ADD_USER_H

#include <QDialog>
#include <iostream>
#include <id_sql.h>

namespace Ui {
class add_user;
}

class add_user : public QDialog
{
    Q_OBJECT

public:
    explicit add_user(QWidget *parent = 0);
    ~add_user();
     ID_SQL *sql;

     void del_user();
     void add_users();

     int        _KEY_ID  ;
     string     _RFID_ID ;
     string     _NAME    ;
     string     _SEX     ;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();


    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

signals:
    //void infoSend(QString,QString,QString);


private:
    Ui::add_user *ui;


};

#endif // ADD_USER_H
