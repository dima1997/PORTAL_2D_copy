#ifndef LOGIN_NEW_H
#define LOGIN_NEW_H

#include <QWidget>

#include <cstdint>

class LoginNew : public QWidget {
public:
    LoginNew(bool & newed, uint8_t & mapId, QWidget *parent = 0);
    virtual ~LoginNew();
    void setMapIds(std::vector<uint8_t> & mapIds);
private:
    bool & newed;
    uint8_t & mapId;
    void newGame();
    void connectEvents();
};

#endif // LOGIN_NEW_H