//
// Created by jay on 7/8/26.
//

#ifndef JSB_GLRENDERER_H
#define JSB_GLRENDERER_H
#include <memory>
#include <string>

#include "Shader.h"
#include "Texture.h"
#include "shared/RendererPayload.hpp"


class GLRenderer {
public:
    GLRenderer();
    void render(const RendererPayload &payload) const;

private:
    unsigned int VBO{};
    unsigned int VAO{};
    unsigned int EBO{};

    std::unique_ptr<Shader> groundShader_;
    //std::unique_ptr<Shader> skyShader_;
    std::unique_ptr<Texture> groundTexture_;

    std::string loadShader(const char *path);
};


#endif //JSB_GLRENDERER_H
