#ifndef RENDERIZABLE_H
#define RENDERIZABLE_H

class Renderizable {
public:
    Renderizable() {}
    virtual ~Renderizable() {}
    virtual void render(float adjuster) = 0;
};

#endif // RENDERIZABLE_H
