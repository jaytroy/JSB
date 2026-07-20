//
// Created by jay on 7/20/26.
//

#ifndef JSB_TEXTURE_H
#define JSB_TEXTURE_H


class Texture {
public:
    Texture(const char* texturePath);
    void use();

private:
    unsigned int texture{};
};


#endif //JSB_TEXTURE_H
