#ifndef LOGIN_JOIN_H
#define LOGIN_JOIN_H

#include <QWidget>

#include <cstdint>

class LoginJoin : public QWidget {
public:
    LoginJoin(bool & joined, uint8_t & gameId, QWidget * parent = 0);
    virtual ~LoginJoin();
    void setGameIds(std::vector<uint8_t> & gameIds);
private:
    bool & joined;
    uint8_t & gameId;
    void joinGame();
    void connectEvents();
};

#endif // LOGIN_JOIN_H
