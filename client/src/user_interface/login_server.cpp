#include "../../includes/user_interface/login_server.h"

#include "ui_LoginServer.h"

#include "../../includes/user_interface/login_mode.h"

#include <QWidget>
#include <QMessageBox>

#include <connector/socket_exception.h>

#include <sstream>

LoginServer::LoginServer(LoginMode & loginMode, QWidget *parent)
:   QWidget(parent), 
    loginMode(loginMode) 
{
    this->hide();

    Ui::LoginServer loginServer;
    loginServer.setupUi(this);
}

LoginServer::~LoginServer() = default;

void LoginServer::login(){
    this->hide();
    QLineEdit* lineIp = findChild<QLineEdit*>("lineIp");
    QString ipQStr = lineIp->text();
    std::string ipStr = ipQStr.toUtf8().constData();
    QLineEdit* linePort = findChild<QLineEdit*>("linePort");
    QString portQStr = linePort->text();
    std::string portStr = portQStr.toUtf8().constData();
    try {
        Connector connector(ipStr, portStr);
        this->loginMode.set_connector(connector);
        QMessageBox qMsg;
        qMsg.setWindowTitle("Portal");
        std::stringstream ok;
        ok << "Connection Success.\n";
        qMsg.setText(QString(ok.str().c_str()));
        qMsg.exec();
        this->close();
        emit login_server_success();
        return;
    } catch (SocketException & error){
        QMessageBox qMsg;
        qMsg.setWindowTitle("Portal");
        std::stringstream err;
        err << "Connection Failed.\n";
        err << "Check ip/port.\n";
        err << "Maybe server is not working.\n"; 
        qMsg.setText(QString(err.str().c_str()));
        qMsg.setIcon(QMessageBox::Warning);
        qMsg.exec();
        this->close();
        emit login_server_failed();
        return;
    }
}

void LoginServer::connect_events(){
    QPushButton* buttonLogin = findChild<QPushButton*>("buttonLogin");
    QObject::connect(buttonLogin, &QPushButton::clicked,
                     this, &LoginServer::login);
}