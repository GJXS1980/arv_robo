/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qvideowidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *pixLabel;
    QWidget *widget_2;
    QLabel *IDLabel;
    QLabel *set_ID;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *nameLabel;
    QLabel *set_name;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *nameLabel_2;
    QLabel *set_tempture;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *quitBtn;
    QVideoWidget *Image_viewer;
    QPushButton *pushButton;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(956, 653);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(30, 20, 518, 518));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pixLabel = new QLabel(widget);
        pixLabel->setObjectName(QString::fromUtf8("pixLabel"));
        pixLabel->setPixmap(QPixmap(QString::fromUtf8(":/UI500x500.png")));

        horizontalLayout->addWidget(pixLabel);

        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(560, 330, 301, 71));
        IDLabel = new QLabel(widget_2);
        IDLabel->setObjectName(QString::fromUtf8("IDLabel"));
        IDLabel->setGeometry(QRect(9, 9, 64, 41));
        QFont font;
        font.setPointSize(20);
        IDLabel->setFont(font);
        set_ID = new QLabel(widget_2);
        set_ID->setObjectName(QString::fromUtf8("set_ID"));
        set_ID->setGeometry(QRect(84, 19, 201, 41));
        set_ID->setFont(font);
        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(590, 120, 301, 71));
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        nameLabel = new QLabel(widget_3);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        nameLabel->setFont(font);

        horizontalLayout_3->addWidget(nameLabel);

        set_name = new QLabel(widget_3);
        set_name->setObjectName(QString::fromUtf8("set_name"));
        set_name->setFont(font);

        horizontalLayout_3->addWidget(set_name);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        widget_4 = new QWidget(centralwidget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(590, 200, 301, 71));
        horizontalLayout_4 = new QHBoxLayout(widget_4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        nameLabel_2 = new QLabel(widget_4);
        nameLabel_2->setObjectName(QString::fromUtf8("nameLabel_2"));
        nameLabel_2->setFont(font);

        horizontalLayout_4->addWidget(nameLabel_2);

        set_tempture = new QLabel(widget_4);
        set_tempture->setObjectName(QString::fromUtf8("set_tempture"));
        set_tempture->setFont(font);

        horizontalLayout_4->addWidget(set_tempture);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        quitBtn = new QPushButton(centralwidget);
        quitBtn->setObjectName(QString::fromUtf8("quitBtn"));
        quitBtn->setGeometry(QRect(800, 480, 101, 71));
        quitBtn->setFont(font);
        Image_viewer = new QVideoWidget(centralwidget);
        Image_viewer->setObjectName(QString::fromUtf8("Image_viewer"));
        Image_viewer->setGeometry(QRect(49, 110, 471, 331));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(610, 480, 101, 71));
        pushButton->setFont(font);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(580, 290, 321, 161));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 956, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pixLabel->setText(QString());
        IDLabel->setText(QCoreApplication::translate("MainWindow", "\345\215\241\345\217\267:", nullptr));
        set_ID->setText(QString());
        nameLabel->setText(QCoreApplication::translate("MainWindow", "\345\220\215\345\255\227:", nullptr));
        set_name->setText(QString());
        nameLabel_2->setText(QCoreApplication::translate("MainWindow", "\344\275\223\346\270\251:", nullptr));
        set_tempture->setText(QString());
        quitBtn->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "                                      logo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
