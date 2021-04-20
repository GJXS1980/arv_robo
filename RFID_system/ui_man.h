/********************************************************************************
** Form generated from reading UI file 'man.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAN_H
#define UI_MAN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_man
{
public:
    QLabel *label;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;

    void setupUi(QDialog *man)
    {
        if (man->objectName().isEmpty())
            man->setObjectName(QStringLiteral("man"));
        man->resize(467, 282);
        label = new QLabel(man);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(180, 82, 141, 71));
        layoutWidget = new QWidget(man);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 220, 371, 33));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout->addWidget(pushButton_3);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton_4 = new QPushButton(layoutWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout->addWidget(pushButton_4);


        retranslateUi(man);

        QMetaObject::connectSlotsByName(man);
    } // setupUi

    void retranslateUi(QDialog *man)
    {
        man->setWindowTitle(QApplication::translate("man", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("man", "                             \346\205\247\350\260\267", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("man", "\346\267\273\345\212\240\346\226\260\346\210\220\345\221\230", Q_NULLPTR));
        pushButton->setText(QApplication::translate("man", "\346\265\217\350\247\210\346\210\220\345\221\230", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("man", "\345\210\240\351\231\244\346\210\220\345\221\230", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("man", "\346\270\205\347\251\272\347\224\250\346\210\267", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class man: public Ui_man {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAN_H
