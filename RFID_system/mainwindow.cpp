#include "mainwindow.h"
#include "card.h"
#include "process.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QtConcurrentRun>
#include <QDebug>
#include <QLabel>
#include <QDateTime>
#include <id_sql.h>
#include <QMessageBox>
#include <show_user.h>
#include <QCameraInfo>
#include <QList>

extern QSqlDatabase db;
extern QSqlQuery query;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),temper(0)
{
    ui->setupUi(this);
     // 打开并连接数据库
     if(!db.open())
     {
        qDebug() << "打开数据库失败"<<endl;
     }
     sql = new ID_SQL(query);


//************************************************************
     Administrator = new man(this);
     my_Thread1 = new Process(this);
     my_Thread2 = new Process2(this);

     my_Thread1->start();
     my_Thread2->start();

    t  = new QTimer(this);
    t2 = new QTimer(this);

     QTimer *timer = new QTimer(this);           //实时定时器

     connect(ui->quitBtn,&QPushButton::clicked,[=](){    //退出程序按钮
        QApplication* app;
        app->exit(0);
    });

    connect(t,&QTimer::timeout,this,&MainWindow::clear);               //定时器触发界面清理
    connect(timer,&QTimer::timeout,this,&MainWindow::timeupdate);      //定时器触发时间更新

    //接收子线程发来的数据
    connect(my_Thread1,&Process::send_rifdID,this, &MainWindow::GET_RFID);
    connect(my_Thread2,&Process2::send_Temperature,this, &MainWindow::GET_MLX90614);

    QList <QCameraInfo> CamList = QCameraInfo::availableCameras();

    //cout<<CamList.count()<<endl;
    if(CamList.count())
    {
        m_camera = new QCamera(CamList.at(0));                         //初始化相机
        //m_camera = new QCamera(this);
        m_camera->setCaptureMode(QCamera::CaptureVideo);                //获取视频
        m_camera->setViewfinder(ui->Image_viewer);                      //视频放置在Image_viewer控件上
        ui->Image_viewer->raise();                                      //将视频放在最上层

        m_camera->start();                                               //开始获取
        ui->Image_viewer->hide();                                        //隐藏控件

    }
    else
   {
        int ret = QMessageBox::question(this, "提示", "未发现摄像头设备,是否继续？", QMessageBox::Yes, QMessageBox::No);

        if(ret == QMessageBox::No)
        {
             exit(0);
        }

   }

    timer->start(10);
    t->start(5000);                                                   //定时器3s
    t2->start(300);
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->setPixmap(QString(":/HG.ico"));

}

void MainWindow::GET_RFID(char *get_ID)
{
    string name;
    char temp_buf[20] = {0};

    db.open();

    ui->Image_viewer->show();                           //显示控件

    ui->set_ID->setText(get_ID);                       //显示数据

    sql->sqlite_seach(query,get_ID,name);
    ui->set_name->setText(name.c_str());

    sprintf(temp_buf,"%.2f",temper);

    ui->set_tempture->setText(temp_buf);

    if(temper >= 37.3)
    {
        qDebug()<<"体温异常！！！";
        ui->label->setPixmap(QString(":/nopass"));
    }
    else
    {
          ui->label->setPixmap(QString(":/pass"));
    }

    temper = 0;
    db.close();
}

void MainWindow::GET_MLX90614(float get_TEMP)     //获取数据
{
    temper = get_TEMP;
    cout << "体温:" << temper << endl;

}

void MainWindow::clear()
{
    char nothing[10] = {};
    ui->set_ID->setText(nothing);                       //清空信息
    ui->set_name->setText(nothing);
    ui->set_tempture->setText(nothing);
    ui->Image_viewer->hide();

    ui->label->setPixmap(QString(":/HG.ico"));
}

void MainWindow::timeupdate()
{
    QDateTime currentTime= QDateTime::currentDateTime();
    QString Timestr=currentTime.toString("yyyy年-MM月-dd日 hh:mm:ss");//时间格式化
    currentTimeLabel->setText(Timestr);
    ui->statusbar->addWidget(currentTimeLabel);
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();             //close sql
}


void MainWindow::on_pushButton_clicked()
{
    Administrator->setAttribute(Qt::WA_ShowModal,true);
    Administrator->show();

}
