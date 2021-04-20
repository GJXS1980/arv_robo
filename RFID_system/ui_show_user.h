/********************************************************************************
** Form generated from reading UI file 'show_user.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOW_USER_H
#define UI_SHOW_USER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_show_user
{
public:
    QLabel *label;
    QTableView *tableView;

    void setupUi(QWidget *show_user)
    {
        if (show_user->objectName().isEmpty())
            show_user->setObjectName(QStringLiteral("show_user"));
        show_user->resize(500, 300);
        label = new QLabel(show_user);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(210, 0, 101, 31));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        tableView = new QTableView(show_user);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(10, 40, 481, 251));

        retranslateUi(show_user);

        QMetaObject::connectSlotsByName(show_user);
    } // setupUi

    void retranslateUi(QWidget *show_user)
    {
        show_user->setWindowTitle(QApplication::translate("show_user", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("show_user", "\346\210\220\345\221\230\345\210\227\350\241\250", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class show_user: public Ui_show_user {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOW_USER_H
