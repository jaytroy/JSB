//
// Created by jay on 7/8/26.
//

#ifndef JSB_SHADER_H
#define JSB_SHADER_H
#include <string>
#include <glm/fwd.hpp>

#include "glad/glad.h"


class Shader {
public:
    Shader(const char* vertPath, const char* fragPath);
    void use();
    void setMat4(const char* name, const glm::mat4& m);
    void setVec3(const char* name, const glm::vec3& v);
    void setFloat(const char* name, float f);

    void setInt(const char *name, int i);

private:
    unsigned int program_;
    std::string loadShader(const char* path);
    int success;
    char infoLog[512];
    unsigned int shaderProgram;
    GLint modelLoc, viewLoc, projLoc;
};


#endif //JSB_SHADER_H

