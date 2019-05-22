#ifndef TEXTURE_H
#define TEXTURE_H

class Texture {
private:
    BigTexture & bigTexture;
    Area areaMap;
    std::unique_ptr<SpriteStrategy> ptrSpriteStrategy;
public:
    Texture(BigTexture & bigTexture, Area areaMap, 
        std::unique_ptr<SpriteStrategy> ptrSpriteStrategy);
    ~Texture();
    void move_to(float x, float y);
    void switch();
    void render(float adjuster, const Area & areaCamera);
    Area getVisionArea();
};

#endif // TEXTURE_H