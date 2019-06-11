/********************************************************************************
** Form generated from reading UI file 'LoginJoin.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINJOIN_H
#define UI_LOGINJOIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginJoin
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelChooseGameId;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelGameId;
    QComboBox *comboBoxGameId;
    QPushButton *buttonJoin;

    void setupUi(QWidget *LoginJoin)
    {
        if (LoginJoin->objectName().isEmpty())
            LoginJoin->setObjectName(QStringLiteral("LoginJoin"));
        LoginJoin->resize(400, 300);
        verticalLayout = new QVBoxLayout(LoginJoin);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        labelChooseGameId = new QLabel(LoginJoin);
        labelChooseGameId->setObjectName(QStringLiteral("labelChooseGameId"));

        verticalLayout->addWidget(labelChooseGameId);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelGameId = new QLabel(LoginJoin);
        labelGameId->setObjectName(QStringLiteral("labelGameId"));

        horizontalLayout_2->addWidget(labelGameId);

        comboBoxGameId = new QComboBox(LoginJoin);
        comboBoxGameId->setObjectName(QStringLiteral("comboBoxGameId"));

        horizontalLayout_2->addWidget(comboBoxGameId);


        horizontalLayout->addLayout(horizontalLayout_2);

        buttonJoin = new QPushButton(LoginJoin);
        buttonJoin->setObjectName(QStringLiteral("buttonJoin"));

        horizontalLayout->addWidget(buttonJoin);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(LoginJoin);

        QMetaObject::connectSlotsByName(LoginJoin);
    } // setupUi

    void retranslateUi(QWidget *LoginJoin)
    {
        LoginJoin->setWindowTitle(QApplication::translate("LoginJoin", "Form", 0));
        labelChooseGameId->setText(QApplication::translate("LoginJoin", "Choose a game id and push on \"join\"", 0));
        labelGameId->setText(QApplication::translate("LoginJoin", "Game id :", 0));
        buttonJoin->setText(QApplication::translate("LoginJoin", "Join", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginJoin: public Ui_LoginJoin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINJOIN_H
