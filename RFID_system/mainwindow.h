#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include "mainwindow.h"
#include "card.h"
#include <QMainWindow>
#include <QCamera>
#include <QTimer>
#include <QLabel>
#include "card.h"
#include <id_sql.h>
#include "process.h"
#include "man.h"
#include "add_user.h"
#include "show_user.h"
#include <QCameraInfo>
#include <QCamera>
#include <QCameraViewfinder>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

     float temper;
     int   ui_flag;

     Process * my_Thread1;
     Process2 * my_Thread2;
     ID_SQL *sql;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void GET_RFID(char *get_ID);  //获取数据
    void GET_MLX90614(float get_TEMP);  //获取数据
    void clear();   //清除画面中的内容
    void timeupdate();  //时间显示更新

    man *Administrator;

public slots:
    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;

    QCamera *m_camera;
    QCameraViewfinder *m_viewfinder;
    QMap<QString, QCameraInfo> m_cameraMap; // name ,info

    QTimer *t;  //延时定时器
    QTimer *t2;  //延时定时器

    QLabel *currentTimeLabel = new QLabel;
};
#endif // MAINWINDOW_H

