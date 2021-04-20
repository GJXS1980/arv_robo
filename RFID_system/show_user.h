#ifndef SHOW_USER_H
#define SHOW_USER_H

#include <QDialog>
#include <id_sql.h>
#include <QStandardItemModel>

namespace Ui {
class show_user;
}

class show_user : public QDialog
{
    Q_OBJECT
public:
    explicit show_user(QDialog *parent = 0);
    ~show_user();
    ID_SQL *sql;
    QStandardItemModel *m_model;

    void show_number();

private:
    Ui::show_user *ui;
};

#endif // SHOW_USER_H
