#include "../../includes/user_interface/game_over.h"

#include "ui_GameOver.h"

#include "../../includes/threads/play_result.h"

#include <QWidget>
#include <QFont>

#include <string>

/*
PRE: Recibe un resultado de juego.
POST:Iniicaliza una ventana de fin de juego.
*/
GameOver::GameOver(PlayResult & playResult, QWidget *parent)
:   QWidget(parent)
{
    Ui::GameOver gameOver;
    gameOver.setupUi(this);
    this->hide();
    this->set_game_status(playResult);
    this->set_players_status(playResult);
}

/*
PRE: Recibe el resultado de un juego.
POST: Setea la etiqueta de estado del juego.
*/
void GameOver::set_game_status(PlayResult & playResult){
    QLabel* gameStatusLabel = findChild<QLabel*>("gameStatusLabel");
    GameStatus gameStatus = playResult.get_game_status();
    if (gameStatus == GAME_STATUS_WON){
       gameStatusLabel->setText("WON");
    } else if (gameStatus == GAME_STATUS_LOST){
       gameStatusLabel->setText("LOST");
    } else {
       gameStatusLabel->setText("NOT_FINISHED");
    }
    gameStatusLabel->setStyleSheet("QLabel { color : white; font-size: 20pt }");
}

/*
PRE: Recibe el resultado de un juego.
POST: Setea el estado de los jugadores en el text browser.
*/
void GameOver::set_players_status(PlayResult & playResult){
    QTextBrowser* playersStatusTextBrowser = 
        findChild<QTextBrowser*>("playersStatusTextBrowser");
    std::string playersStatusStr = playResult.get_players_status();
    playersStatusTextBrowser->append(playersStatusStr.c_str());
}

/*Destruye ventantana.*/
GameOver::~GameOver() = default;