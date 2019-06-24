#include "../../includes/user_interface/game_over.h"

#include "ui_GameOver.h"

#include "../../includes/threads/play_result.h"

#include <QWidget>
#include <QFont>

#include <string>

GameOver::GameOver(PlayResult & playResult, QWidget *parent)
:   QWidget(parent)
{
    Ui::GameOver gameOver;
    gameOver.setupUi(this);
    this->hide();
    this->set_game_status(playResult);
    this->set_players_status(playResult);
}

void GameOver::set_game_status(PlayResult & playResult){
    QLabel* gameStatusLabel = findChild<QLabel*>("gameStatusLabel");
    GameStatus gameStatus = playResult.get_game_status();
    if (gameStatus == WON){
       gameStatusLabel->setText("WON");
    } else if (gameStatus == LOST){
       gameStatusLabel->setText("LOST");
    } else {
       gameStatusLabel->setText("NOT_FINISHED");
    }
    gameStatusLabel->setStyleSheet("QLabel { color : white; font-size: 20pt }");
}

void GameOver::set_players_status(PlayResult & playResult){
    QTextBrowser* playersStatusTextBrowser = 
        findChild<QTextBrowser*>("playersStatusTextBrowser");
    std::string playersStatusStr = playResult.get_players_status();
    playersStatusTextBrowser->append(playersStatusStr.c_str());
}

GameOver::~GameOver() = default;