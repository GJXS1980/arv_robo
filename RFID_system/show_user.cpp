#include "show_user.h"
#include "ui_show_user.h"
#include <id_sql.h>
#include <QDebug>
#include <QHeaderView>
#include <QStringList>
#include <QStandardItemModel>
#include <QString>

#define ARR_MAX 300

extern QSqlDatabase db;
extern QSqlQuery query;

show_user::show_user(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::show_user)
{
    ui->setupUi(this);

    db.close();
    // 打开并连接数据库
    if(!db.open())
    {
       qDebug() << "打开数据库失败"<<endl;
    }
    sql = new ID_SQL(query);

    this->setGeometry(700,350,500,300);
    this->setWindowTitle("浏览成员");
    ui->label->setStyleSheet("color:red");

    QStringList strHeader;
    m_model = new QStandardItemModel(this);

        //初始化表头属性，后面有需要可设计不同表头属性
    strHeader<<QString::fromLocal8Bit("序号")<<QString::fromLocal8Bit("卡号")
                <<QString::fromLocal8Bit("姓名")<<QString::fromLocal8Bit("性别");

    m_model->setHorizontalHeaderLabels(strHeader);
    ui->tableView->setModel(m_model);

    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setColumnWidth(0,50);
    ui->tableView->setColumnWidth(1,200);
    ui->tableView->showGrid();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);         //col is not set w
}

void show_user::show_number()
{
    db.open();
    int         i                = 0;
    int         KEY_ID[ARR_MAX]  = {0};
    string     _ID[ARR_MAX];
    string     _NAME[ARR_MAX];
    string     _SEX[ARR_MAX];

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->verticalHeader()->setVisible(false);

    sql->sqlite_show(query,KEY_ID,_ID,_NAME,_SEX);

    while (KEY_ID[i])
    {
        //qDebug() << qPrintable(QString("序号:[%1]\t 卡号%2\t 姓名:%3\t 性别:%4").arg(KEY_ID[i]).arg(_ID[i].c_str()).arg(_NAME[i].c_str()).arg(_SEX[i].c_str()));

          for(int column=0; column<4; column++)
          {

               if(column == 0)
               {
                         QStandardItem *item = new QStandardItem(QString("%0").arg(KEY_ID[i]));
                         m_model->setItem(i,column,item);
                }
                else if(column == 1)
                {
                        QStandardItem *item = new QStandardItem(_ID[i].c_str());
                        m_model->setItem(i,column,item);
                }
                else if(column == 2)
                 {
                         QStandardItem *item = new QStandardItem(_NAME[i].c_str());
                         m_model->setItem(i,column,item);
                }
               else if(column == 3)
               {
                        QStandardItem *item = new QStandardItem(_SEX[i].c_str());
                        m_model->setItem(i,column,item);
                }

          }

      i++;
    }




    db.close();

}





show_user::~show_user()
{
    delete ui;
}
