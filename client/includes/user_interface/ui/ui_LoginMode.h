/********************************************************************************
** Form generated from reading UI file 'LoginModecF8228.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef LOGINMODECF8228_H
#define LOGINMODECF8228_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginMode
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *buttonNew;
    QPushButton *buttonJoin;

    void setupUi(QWidget *LoginMode)
    {
        if (LoginMode->objectName().isEmpty())
            LoginMode->setObjectName(QStringLiteral("LoginMode"));
        LoginMode->resize(400, 300);
        verticalLayout = new QVBoxLayout(LoginMode);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        buttonNew = new QPushButton(LoginMode);
        buttonNew->setObjectName(QStringLiteral("buttonNew"));

        verticalLayout->addWidget(buttonNew);

        buttonJoin = new QPushButton(LoginMode);
        buttonJoin->setObjectName(QStringLiteral("buttonJoin"));

        verticalLayout->addWidget(buttonJoin);


        retranslateUi(LoginMode);

        QMetaObject::connectSlotsByName(LoginMode);
    } // setupUi

    void retranslateUi(QWidget *LoginMode)
    {
        LoginMode->setWindowTitle(QApplication::translate("LoginMode", "Form", 0));
        buttonNew->setText(QApplication::translate("LoginMode", "New Game", 0));
        buttonJoin->setText(QApplication::translate("LoginMode", "Join Game", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginMode: public Ui_LoginMode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LOGINMODECF8228_H
