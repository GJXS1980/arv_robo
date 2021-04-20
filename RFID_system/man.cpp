#include "man.h"
#include "ui_man.h"
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>


extern QSqlDatabase db;
extern QSqlQuery query;


man::man(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::man)
{
    ui->setupUi(this);

    db.close();
    // 打开并连接数据库
    if(!db.open())
    {
       qDebug() << "打开数据库失败"<<endl;
    }
    sql  = new ID_SQL(query);

    scan = new show_user(this);
    add  = new add_user(this);

    this->setGeometry(700,350,500,300);
    this->setWindowTitle(QString("管理员设置"));
    ui->label->setPixmap(QString(":/HG.ico"));

    ui->pushButton_3->setFocusPolicy(Qt::NoFocus);
    ui->pushButton->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_2->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_4->setFocusPolicy(Qt::NoFocus);

}

man::~man()
{
    delete ui;
}


void man::info_Recv_Repeat(QString _ID,QString _NAME,QString _SEX)
{
    emit info_Send_Repeat(_ID,_NAME,_SEX);
}


void man::on_pushButton_3_clicked()     //添加成员
{
    add->setAttribute(Qt::WA_ShowModal,true);
    add->show();
    add->add_users();

}

void man::on_pushButton_clicked()       //浏览成员
{
    scan->setGeometry(700,350,500,300);
    scan->setAttribute(Qt::WA_ShowModal,true);

    scan->show();
    scan->show_number();

}

void man::on_pushButton_2_clicked()     //删除成员
{
    add->setAttribute(Qt::WA_ShowModal,true);
    add->show();
    add->del_user();

}


void man::on_pushButton_4_clicked()
{
    int ret = QMessageBox::question(this, "警示", "点击确定是否清空用户信息表？", QMessageBox::Yes, QMessageBox::No);

    if(ret == QMessageBox::Yes)
     {
         qDebug() << "YES"<<endl;
         query.exec("DROP TABLE ID_SYSTEM");        //先清空一下表
     }
    else if(ret == QMessageBox::No)
        qDebug ()<< "No"<<endl;
}
