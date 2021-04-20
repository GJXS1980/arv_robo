#ifndef ID_SQL_H
#define ID_SQL_H

#include <iostream>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QFile>
#include <QByteArray>
#include <QString>
#include <QStringList>
#include <QApplicationStateChangeEvent>

//相关操作宏定义
#define create_sql          "CREATE TABLE IF NOT EXISTS ID_SYSTEM (序号 INTEGER PRIMARY KEY AUTOINCREMENT, 卡号 varchar(50),名字 varchar(30),性别 varchar(10))"
#define select_max_sql      "select max(id) from ID_SYSTEM";
#define insert_sql          "insert into ID_SYSTEM values (null,?,?,?)"
#define update_ID           "update ID_SYSTEM set 卡号 =:ID where 序号 =:KEY_ID"
#define update_NAME         "update ID_SYSTEM set 名字 =:NAME where 序号 =:KEY_ID"
#define update_SEX          "update ID_SYSTEM set 性别 =:SEX where 序号 =:KEY_ID"
#define select_sql          "select 卡号 from ID_SYSTEM"
#define select_all_sql      "select * from ID_SYSTEM"
#define search_sql          "select * from ID_SYSTEM where 卡号 = ? "

#define dele_search         "select * from ID_SYSTEM where 卡号 = ? OR 名字 = ?"
#define delete_sql          "delete from ID_SYSTEM where 卡号 = ? OR 名字 = ?"

#define clear_sql           "delete from ID_SYSTEM"
#define find_sql            "SELECT * FROM ID_SYSTEM WHERE licence like ?"

#include <QObject>


using namespace std;

class ID_SQL:public QObject
{
      Q_OBJECT
public:
    ID_SQL( QSqlQuery query);
    ~ID_SQL();

    void delete_db(void);
    void delete_tables(QSqlQuery query);
    void sqlite_add(QSqlQuery query,string ID,string NAME,string SEX);
    void sqlite_seach(QSqlQuery query,string ID,string &Name);
    void sqlite_delete(QSqlQuery query,string ID);
    void sqlite_update(QSqlQuery query,int KEY_ID);
    void sqlite_show(QSqlQuery query,int *KEY,string *ID,string *NAME,string *SEX);
    void search_delete(QSqlQuery query,int &KEY,string &ID,string &NAME,string &SEX);
    void delete_usear(QSqlQuery query,string ID,string NAME);

signals:
    void sqlsig();
};

#endif // ID_SQL_H
