#ifndef MAN_H
#define MAN_H

#include <QDialog>
#include "add_user.h"
#include "show_user.h"
#include <id_sql.h>

namespace Ui {
class man;
}

class man : public QDialog
{
    Q_OBJECT

public:
    explicit man(QWidget *parent = 0);
    ~man();

    add_user    *add;
    show_user   *scan;
    ID_SQL *sql;

public slots:
    void info_Recv_Repeat(QString _ID,QString _NAME,QString _SEX);
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

signals:
    void info_Send_Repeat(QString,QString,QString);                  //中转
    void  pushButton_2_press();


private slots:
    void on_pushButton_4_clicked();

private:
    Ui::man *ui;
};

#endif // MAN_H
