//
// Created by jay on 7/8/26.
//

#include "GLRenderer.h"

#include <cstddef>
#include <format>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <bits/atomic_base.h>
#include <glad/glad.h>

GLRenderer::GLRenderer() {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        -0.0f, -0.5f, 0.5f,
        0.0f, 0.5f, 0.0f,
    };

    //Set up OpenGL objects
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Compile vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertex_shader = loadShader(SHADER_DIR "vertex.glsl");
    const char* vertex_shader_ptr = vertex_shader.c_str();
    glShaderSource(vertexShader, 1, &vertex_shader_ptr, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        throw std::runtime_error(std::string("Failed to create vertex shader") + infoLog);
    }

    //Compile fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragment_shader = loadShader(SHADER_DIR "fragment.glsl");
    const char* fragment_shader_ptr = fragment_shader.c_str();
    glShaderSource(fragmentShader, 1, &fragment_shader_ptr, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        throw std::runtime_error(std::string("Failed to create fragment shader") + infoLog);
    }

    //Create shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        throw std::runtime_error(std::string("Failed to create shader program") + infoLog);
    }


    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void GLRenderer::render() {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

std::string GLRenderer::loadShader(const char *path) {
    std::ifstream f(path);
    if (!f) {
        throw std::runtime_error(std::string("Shader not found ") + path);
    }
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}
