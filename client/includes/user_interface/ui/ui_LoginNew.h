/********************************************************************************
** Form generated from reading UI file 'LoginNew.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINNEW_H
#define UI_LOGINNEW_H

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

class Ui_LoginNew
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelChooseMapId;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBoxMapId;
    QPushButton *buttonNew;

    void setupUi(QWidget *LoginNew)
    {
        if (LoginNew->objectName().isEmpty())
            LoginNew->setObjectName(QStringLiteral("LoginNew"));
        LoginNew->resize(400, 300);
        verticalLayout = new QVBoxLayout(LoginNew);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        labelChooseMapId = new QLabel(LoginNew);
        labelChooseMapId->setObjectName(QStringLiteral("labelChooseMapId"));

        verticalLayout->addWidget(labelChooseMapId);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        comboBoxMapId = new QComboBox(LoginNew);
        comboBoxMapId->setObjectName(QStringLiteral("comboBoxMapId"));

        horizontalLayout->addWidget(comboBoxMapId);

        buttonNew = new QPushButton(LoginNew);
        buttonNew->setObjectName(QStringLiteral("buttonNew"));

        horizontalLayout->addWidget(buttonNew);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(LoginNew);

        QMetaObject::connectSlotsByName(LoginNew);
    } // setupUi

    void retranslateUi(QWidget *LoginNew)
    {
        LoginNew->setWindowTitle(QApplication::translate("LoginNew", "Form", 0));
        labelChooseMapId->setText(QApplication::translate("LoginNew", "Choose a map id and push on \"new\" button", 0));
        buttonNew->setText(QApplication::translate("LoginNew", "new", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginNew: public Ui_LoginNew {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINNEW_H
