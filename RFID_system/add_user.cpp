#include "add_user.h"
#include "ui_add_user.h"
#include <QDebug>
#include <iostream>
#include <QMessageBox>
#include "man.h"
using namespace std;

extern QSqlDatabase db;
extern QSqlQuery query;

add_user::add_user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_user)
{
    ui->setupUi(this);

    db.close();
    // 打开并连接数据库
    if(!db.open())
    {
       qDebug() << "打开数据库失败"<<endl;
    }
    sql = new ID_SQL(query);

    ui->pushButton_3->setFocusPolicy(Qt::NoFocus);
    ui->pushButton->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_2->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_4->setFocusPolicy(Qt::NoFocus);

}

add_user::~add_user()
{
    delete ui;
}

void add_user::on_pushButton_clicked()
{
    ui->LineEdit->setFocus();

    string ID = ui->LineEdit->text().toStdString();
    string name = ui->LineEdit_2->text().toStdString();
    string sex = ui->ComboBox->currentText().toStdString();

    if( !ID.length() || !name.length() || sex.length() > 3)
    {
        QMessageBox::information(this,"提示",QString("用户信息未完整"));             //检测信息是否完整
    }
    else
    {
          db.open();
          sql->sqlite_add(query,ID,name,sex);
          QMessageBox::information(this,"提示",QString("新用户添加成功"));
          db.close();
    }

 }

void add_user::on_pushButton_2_clicked()
{
   ui->LineEdit->clear();
   ui->LineEdit_2->clear();
   ui->ComboBox->setCurrentIndex(0);

   db.close();
   this-> close();

}

void add_user::add_users()
{

    this->setGeometry(700,350,500,300);

    this->setWindowTitle("用户信息");
    ui->label->setText("\t请输入删除用户");
    ui->label->setStyleSheet("color:red");
    ui->LineEdit->setPlaceholderText("  必填  (可刷卡输入)");
    ui->LineEdit_2->setPlaceholderText("  必填 ");
    ui->LineEdit->setFocus();
    ui->pushButton_3->setVisible(false);
    ui->pushButton->setVisible(true);

    ui->Label_3->setVisible(true);
    ui->ComboBox->setVisible(true);

    ui->plainTextEdit->setVisible(false);
    ui->pushButton_4->setVisible(false);


}



void add_user::del_user()
{

    this->setWindowTitle("删除用户");
    ui->label->setStyleSheet("color:red");
    ui->label->setText("          请输入删除用户ID或名字");
    ui->LineEdit->setPlaceholderText("  选择输入 ");
    ui->LineEdit_2->setPlaceholderText("  选择输入 ");
    ui->plainTextEdit->setReadOnly(true);

    ui->pushButton_3->setVisible(true);
    ui->pushButton->setVisible(false);

    ui->ComboBox->setVisible(false);
    ui->Label_3->setVisible(false);

    ui->plainTextEdit->setVisible(true);

    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setVisible(true);

    ui->LineEdit->setFocus();
    ui->plainTextEdit->clear();

}



void add_user::on_pushButton_3_clicked()
{

    db.open();
    int ret = QMessageBox::question(this, "警示", "点击确定是否删除用户？", QMessageBox::Yes, QMessageBox::No);
    if(ret == QMessageBox::Yes)
    {
         //qDebug() << "YES"<<endl;
         sql->delete_usear(query,_RFID_ID,_NAME);

    }
    else if(ret == QMessageBox::No)
          //qDebug ()<< "No"<<endl;

    db.close();
}

void add_user::on_pushButton_4_clicked()
{
    char       temp_buf[100] = {0};
     db.open();

    _RFID_ID = ui->LineEdit->text().toStdString();
    _NAME    = ui->LineEdit_2->text().toStdString();

    if(_RFID_ID.length()>2 | _NAME.length()>1)
    {
        sql->search_delete(query,_KEY_ID,_RFID_ID,_NAME,_SEX);

        sprintf(temp_buf,"序号:%d  卡号:%s  姓名:%s  性别:%s ",_KEY_ID,_RFID_ID.c_str(),_NAME.c_str(),_SEX.c_str());

        cout<<"buf:"<<temp_buf<<endl;
        ui->plainTextEdit->setPlainText(temp_buf);

        ui->pushButton_3->setEnabled(true);


    }
    else
    {

        QMessageBox::information(this,"提示",QString("请输入用户信息"));             //检测信息是否完整

    }


    db.close();
}
