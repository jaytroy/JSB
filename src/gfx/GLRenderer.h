//
// Created by jay on 7/8/26.
//

#ifndef JSB_GLRENDERER_H
#define JSB_GLRENDERER_H
#include <memory>
#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Shader.h"
#include "glad/glad.h"


class GLRenderer {
public:
    GLRenderer();
    void render(std::vector<double>& payload);

private:
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    unsigned int texture;

    std::unique_ptr<Shader> groundShader_;
    //std::unique_ptr<Shader> skyShader_;

    std::string loadShader(const char *path);
};


#endif //JSB_GLRENDERER_H
