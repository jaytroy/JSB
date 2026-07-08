//
// Created by jay on 7/8/26.
//

#ifndef JSB_GLRENDERER_H
#define JSB_GLRENDERER_H
#include <string>


class GLRenderer {
public:
    GLRenderer();
    void render();

private:
    unsigned int VBO;
    unsigned int VAO;
    unsigned int shaderProgram;
    int success;
    char infoLog[512];

    std::string loadShader(const char *path);
};


#endif //JSB_GLRENDERER_H
