//
// Created by franciscosicardi on 23/06/19.
//

#ifndef PORTAL_SWITCHABLE_H
#define PORTAL_SWITCHABLE_H


class Switchable {
private:
    bool updated;
protected:
    virtual bool _switchedState(bool updated);
    virtual void _switchState();
public:
    explicit Switchable();
    Switchable(const Switchable &other);
    ~Switchable();
    bool switchedState();
    void switchState();
};


#endif //PORTAL_SWITCHABLE_H
