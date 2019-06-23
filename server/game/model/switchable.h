//
// Created by franciscosicardi on 23/06/19.
//

#ifndef PORTAL_SWITCHABLE_H
#define PORTAL_SWITCHABLE_H


class Switchable {
private:
    bool updated;
    virtual bool _wasUpdated();
public:
    explicit Switchable(bool initState);
    Switchable(const Switchable &other);
    ~Switchable();
    bool wasUpdated();
};


#endif //PORTAL_SWITCHABLE_H
