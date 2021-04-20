/********************************************************************************
** Form generated from reading UI file 'add_user.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_USER_H
#define UI_ADD_USER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_add_user
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *formWidget;
    QFormLayout *formLayout;
    QLabel *Label;
    QLineEdit *LineEdit;
    QLabel *Label_2;
    QLineEdit *LineEdit_2;
    QLabel *Label_3;
    QComboBox *ComboBox;
    QLabel *label;
    QPlainTextEdit *plainTextEdit;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;

    void setupUi(QDialog *add_user)
    {
        if (add_user->objectName().isEmpty())
            add_user->setObjectName(QStringLiteral("add_user"));
        add_user->resize(500, 300);
        pushButton = new QPushButton(add_user);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(290, 250, 89, 25));
        pushButton_2 = new QPushButton(add_user);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(90, 250, 89, 25));
        formWidget = new QWidget(add_user);
        formWidget->setObjectName(QStringLiteral("formWidget"));
        formWidget->setGeometry(QRect(120, 120, 201, 121));
        formLayout = new QFormLayout(formWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        Label = new QLabel(formWidget);
        Label->setObjectName(QStringLiteral("Label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, Label);

        LineEdit = new QLineEdit(formWidget);
        LineEdit->setObjectName(QStringLiteral("LineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, LineEdit);

        Label_2 = new QLabel(formWidget);
        Label_2->setObjectName(QStringLiteral("Label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, Label_2);

        LineEdit_2 = new QLineEdit(formWidget);
        LineEdit_2->setObjectName(QStringLiteral("LineEdit_2"));

        formLayout->setWidget(1, QFormLayout::FieldRole, LineEdit_2);

        Label_3 = new QLabel(formWidget);
        Label_3->setObjectName(QStringLiteral("Label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, Label_3);

        ComboBox = new QComboBox(formWidget);
        ComboBox->setObjectName(QStringLiteral("ComboBox"));

        formLayout->setWidget(2, QFormLayout::FieldRole, ComboBox);

        label = new QLabel(add_user);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 20, 361, 71));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        plainTextEdit = new QPlainTextEdit(add_user);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(70, 190, 321, 41));
        pushButton_3 = new QPushButton(add_user);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(290, 250, 89, 25));
        pushButton_4 = new QPushButton(add_user);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(400, 190, 71, 41));

        retranslateUi(add_user);

        QMetaObject::connectSlotsByName(add_user);
    } // setupUi

    void retranslateUi(QDialog *add_user)
    {
        add_user->setWindowTitle(QApplication::translate("add_user", "Dialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("add_user", "\347\241\256\345\256\232", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("add_user", "\345\217\226\346\266\210", Q_NULLPTR));
        Label->setText(QApplication::translate("add_user", "\345\215\241\345\217\267", Q_NULLPTR));
        Label_2->setText(QApplication::translate("add_user", "\345\247\223\345\220\215", Q_NULLPTR));
        Label_3->setText(QApplication::translate("add_user", "\346\200\247\345\210\253", Q_NULLPTR));
        ComboBox->clear();
        ComboBox->insertItems(0, QStringList()
         << QApplication::translate("add_user", "\350\257\267\351\200\211\346\213\251", Q_NULLPTR)
         << QApplication::translate("add_user", "\347\224\267", Q_NULLPTR)
         << QApplication::translate("add_user", "\345\245\263", Q_NULLPTR)
        );
        label->setText(QApplication::translate("add_user", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\344\277\241\346\201\257", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("add_user", "\345\210\240\351\231\244", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("add_user", "\347\241\256\350\256\244\344\277\241\346\201\257", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class add_user: public Ui_add_user {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_USER_H
