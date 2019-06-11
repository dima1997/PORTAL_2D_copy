/********************************************************************************
** Form generated from reading UI file 'LoginServerHV8228.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef LOGINSERVERHV8228_H
#define LOGINSERVERHV8228_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginServer
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelIp;
    QLineEdit *lineIp;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelPort;
    QLineEdit *linePort;
    QPushButton *buttonLogin;

    void setupUi(QWidget *LoginServer)
    {
        if (LoginServer->objectName().isEmpty())
            LoginServer->setObjectName(QStringLiteral("LoginServer"));
        LoginServer->resize(400, 300);
        verticalLayout = new QVBoxLayout(LoginServer);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelIp = new QLabel(LoginServer);
        labelIp->setObjectName(QStringLiteral("labelIp"));
        labelIp->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(labelIp);

        lineIp = new QLineEdit(LoginServer);
        lineIp->setObjectName(QStringLiteral("lineIp"));

        horizontalLayout->addWidget(lineIp);

        horizontalLayout->setStretch(0, 1);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelPort = new QLabel(LoginServer);
        labelPort->setObjectName(QStringLiteral("labelPort"));
        labelPort->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(labelPort);

        linePort = new QLineEdit(LoginServer);
        linePort->setObjectName(QStringLiteral("linePort"));

        horizontalLayout_2->addWidget(linePort);

        horizontalLayout_2->setStretch(0, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        buttonLogin = new QPushButton(LoginServer);
        buttonLogin->setObjectName(QStringLiteral("buttonLogin"));

        verticalLayout->addWidget(buttonLogin);


        retranslateUi(LoginServer);

        QMetaObject::connectSlotsByName(LoginServer);
    } // setupUi

    void retranslateUi(QWidget *LoginServer)
    {
        LoginServer->setWindowTitle(QApplication::translate("LoginServer", "Form", 0));
        labelIp->setText(QApplication::translate("LoginServer", "I P :", 0));
        labelPort->setText(QApplication::translate("LoginServer", "PORT :", 0));
        buttonLogin->setText(QApplication::translate("LoginServer", "Login", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginServer: public Ui_LoginServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LOGINSERVERHV8228_H
