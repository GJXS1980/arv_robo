#include "mainwindow.h"
#include <QApplication>
#include <QPixmap>
#include <id_sql.h>

QSqlDatabase db;
QSqlQuery query;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //************************************************************
        // 增加本程序SQLite数据库
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("INFO.db");
    query=QSqlQuery(db);   //连接数据库(*******)

    MainWindow w;
    w.setWindowTitle("广州慧谷动力科技有限公司");
    w.setWindowIcon(QPixmap(":/HG.ico"));
    w.setWindowOpacity(0.9);
   //w.setStyleSheet("border-image:url(:/LOGO.png)");
    w.setGeometry(450,200,1000,600);
    w.show();
    return a.exec();
}
