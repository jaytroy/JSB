//
// Created by jay on 7/8/26.
//

#include "Shader.h"

#include <fstream>
#include <sstream>
#include <string>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

/**
 *
 * @param vertPath Path to the vertex shader.
 * @param fragPath Path to the fragment shader.
 */
Shader::Shader(const char* vertPath, const char* fragPath) {
    //Compile vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertex_shader = loadShader(vertPath);
    const char *vertex_shader_ptr = vertex_shader.c_str();
    glShaderSource(vertexShader, 1, &vertex_shader_ptr, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        throw std::runtime_error(std::string("Failed to create vertex shader") + infoLog);
    }

    //Compile fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragment_shader = loadShader(fragPath);
    const char *fragment_shader_ptr = fragment_shader.c_str();
    glShaderSource(fragmentShader, 1, &fragment_shader_ptr, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        throw std::runtime_error(std::string("Failed to create fragment shader") + infoLog);
    }

    //Create shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        throw std::runtime_error(std::string("Failed to create shader program") + infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    if (quadVAO != 0) {
        glDeleteVertexArrays(1, &quadVAO);
    }
    glDeleteProgram(shaderProgram);
}

void Shader::use() {
    glUseProgram(shaderProgram);
}

void Shader::drawFullscreenTriangle() {
    use();
    if (quadVAO == 0) {
        glGenVertexArrays(1, &quadVAO);
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

//glUniform* writes to the program that is currently bound, not the one the
//location was queried from, so every setter binds this program first.
void Shader::setMat4(const char *name, const glm::mat4 &m) {
    use();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::setVec3(const char *name, const glm::vec3 &v) {
    use();
    glUniform3fv(glGetUniformLocation(shaderProgram, name), 1, glm::value_ptr(v));
}

void Shader::setFloat(const char *name, float f) {
    use();
    glUniform1f(glGetUniformLocation(shaderProgram, name), f);
}

void Shader::setInt(const char* name, int i) {
    use();
    glUniform1i(glGetUniformLocation(shaderProgram, name), i);
}

std::string Shader::loadShader(const char *path) {
    std::ifstream f(path);
    if (!f) {
        throw std::runtime_error(std::string("Shader.cpp not found ") + path);
    }
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}