#ifndef GAME_OVER_H
#define GAME_OVER_H

class PlayResult; // fwd

#include <QWidget>
#include <QCloseEvent>

class GameOver : public QWidget {
private:
    void set_game_status(PlayResult & playResult);
    void set_players_status(PlayResult & playResult);
public:
    GameOver(PlayResult & playResult, QWidget *parent = 0);
    virtual ~GameOver();
};

#endif // GAME_OVER_H
