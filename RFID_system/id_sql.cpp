#include "id_sql.h"

ID_SQL::ID_SQL( QSqlQuery query)
{
    //delete_tables(query);       //调试使用 晴空表

    query.prepare(create_sql);
    if(!query.exec())
    {
        qDebug()<<"创建表失败:"<<query.lastError().databaseText();
    }

}

ID_SQL::~ID_SQL()
{
    //db.close();
}



void ID_SQL::delete_db(void)
{
    //删除数据库
    QFile::remove("INFO.db");
}

//***********************对表操作******************
//添加表格
//删除表格
//修改表格
//查看表格

void ID_SQL::delete_tables(QSqlQuery query)
{
    query.exec("DROP TABLE ID_SYSTEM");        //先清空一下表
}

//*********************对列操作********************
//添加列
//删除列
//修改列
//查看列

//**************对记录操作************
//添加记录
void ID_SQL::sqlite_add(QSqlQuery query,string ID,string NAME,string SEX)
{
    //插入数据
    query.prepare(insert_sql);
    query.addBindValue(ID.c_str());
    query.addBindValue(NAME.c_str());
    query.addBindValue(SEX.c_str());

    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    else
    {
        qDebug()<<"insert is ok!";
    }

}



//查找记录
void ID_SQL::sqlite_seach(QSqlQuery query,string ID,string &Name)
{

    int flag = 0;

    query.prepare(search_sql);
    query.addBindValue(ID.c_str());
    if(!query.exec())
    {
        qDebug()<<query.lastError().databaseText();

    }
    else                            //发送命令成功
    {
            while (query.next())         //遍历多个相同的
            {
                flag = 1;
                int         KEY_ID      = query.record().value(0).toInt();
                QString     RFID_ID     = query.record().value(1).toString().trimmed();
                QString     NAME        = query.record().value(2).toString().trimmed();
                QString     SEX         = query.record().value(3).toString().trimmed();


                Name = NAME.toStdString();
                cout<<"\t\t\t<查询结果>"<<endl;
                qDebug() << qPrintable(QString("序号:[%1]\t 卡号%2\t 姓名:%3\t 性别:%4").arg(KEY_ID).arg(RFID_ID).arg(NAME).arg(SEX));
            }

            if(!flag)
            {
                Name = "新用户";
                qDebug()<<"表中没有发现此卡号：["<<ID.c_str()<<"]";
            }

    }

}

//搜索删除
void ID_SQL::search_delete(QSqlQuery query,int &KEY,string &ID,string &NAME,string &SEX)
{
    query.prepare(dele_search);
    query.addBindValue(ID.c_str());
    query.addBindValue(NAME.c_str());
    if(!query.exec())
    {
        qDebug()<<query.lastError().databaseText();

    }
    else                            //发送命令成功
    {
            if(query.next())         //遍历多个相同的
            {
                int         _KEY_ID      = query.record().value(0).toInt();
                QString     _RFID_ID     = query.record().value(1).toString().trimmed();
                QString     _NAME        = query.record().value(2).toString().trimmed();
                QString     _SEX         = query.record().value(3).toString().trimmed();

                KEY =  _KEY_ID;
                ID  =  _RFID_ID.toStdString();
                NAME =  _NAME.toStdString();
                SEX = _SEX.toStdString();

//               qDebug() << qPrintable(QString("序号:[%1]\t 卡号%2\t 姓名:%3\t 性别:%4").arg(_KEY_ID).arg(_RFID_ID).arg(_NAME).arg(_SEX));
            }
            else
            {
                KEY =  0;
                ID  =  "无";
                NAME = "无";
                SEX =  "无";
            }

    }


}
//删除记录
void ID_SQL::delete_usear(QSqlQuery query,string ID,string NAME)
{
    query.prepare(delete_sql);

    query.addBindValue(ID.c_str());
    query.addBindValue(NAME.c_str());
    if(!query.exec())
    {
        qDebug()<<query.lastError().databaseText();

    }
    else
    {
        qDebug()<<"user delete is ok!";
    }




}


//删除记录(ID)
void ID_SQL::sqlite_delete(QSqlQuery query,string ID)
{
    query.prepare(delete_sql);
    query.addBindValue(ID.c_str());
    if(!query.exec())
    {
        qDebug()<<query.lastError().databaseText();
    }
    else
    {
        qDebug()<<"delete is ok!";
    }
}




//更新数据
void ID_SQL::sqlite_update(QSqlQuery query,int KEY_ID)
{
    int i;
    string update;
    cout<<"清输入选择更改的信息: (1)卡号 (2)姓名 (3)性别 "<<endl;
    cin>>i;

     switch (i)
     {
        case 1: cout<<"请输入新的卡号"<<endl;
                cin>>update;
                query.prepare(update_ID);
                query.bindValue(":ID", update.c_str());
                query.bindValue(":KEY_ID", KEY_ID);
                break;

        case 2: cout<<"请输入新的姓名"<<endl;
                cin>>update;
                query.prepare(update_NAME);
                query.bindValue(":NAME", update.c_str());
                query.bindValue(":KEY_ID", KEY_ID);
                break;

        case 3: cout<<"请输入新的性别"<<endl;
                cin>>update;
                query.prepare(update_SEX);
                query.bindValue(":SEX", update.c_str());
                query.bindValue(":KEY_ID", KEY_ID);
                break;

        default: break;
     }

    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    else
    {
        qDebug()<<"update is ok!";
    }

}

//显示记录
void ID_SQL::sqlite_show(QSqlQuery query,int *KEY,string *ID,string *NAME,string *SEX)
{
    int i = 0;
    QString SQL;                        // 存放标准SQL语句
    SQL = "SELECT * FROM ID_SYSTEM";
    if(!query.exec(SQL))
    {
        qDebug() << query.lastError().databaseText();
        return;
    }

    // 以行为单位展示查询结果
    while(query.next())
    {
        int         _KEY_ID      = query.record().value(0).toInt();
        QString     _ID          = query.record().value(1).toString().trimmed();
        QString     _NAME        = query.record().value(2).toString().trimmed();
        QString     _SEX         = query.record().value(3).toString().trimmed();

        KEY[i] =  _KEY_ID;
        ID[i]  =  _ID.toStdString();
        NAME[i]=  _NAME.toStdString();
        SEX[i] = _SEX.toStdString();
        i++;
        //qDebug() << qPrintable(QString("序号:[%1]\t 卡号%2\t 姓名:%3\t 性别:%4").arg(KEY_ID).arg(ID).arg(NAME).arg(SEX));
    }
}
