/********************************************************************************
** Form generated from reading UI file 'show.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOW_H
#define UI_SHOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_show
{
public:
    QLabel *label;
    QTableView *tableView;

    void setupUi(QWidget *show)
    {
        if (show->objectName().isEmpty())
            show->setObjectName(QStringLiteral("show"));
        show->resize(500, 300);
        show->setMinimumSize(QSize(500, 300));
        label = new QLabel(show);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(160, 10, 91, 31));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        label->setFocusPolicy(Qt::TabFocus);
        tableView = new QTableView(show);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(10, 50, 381, 241));

        retranslateUi(show);

        QMetaObject::connectSlotsByName(show);
    } // setupUi

    void retranslateUi(QWidget *show)
    {
        show->setWindowTitle(QApplication::translate("show", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("show", "\346\210\220\345\221\230\345\210\227\350\241\250", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class show: public Ui_show {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOW_H
