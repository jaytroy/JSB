//
// Created by jay on 7/8/26.
//
#include "GLRenderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../external/stb_image.h"

#include <memory>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shared/RendererPayload.hpp"

/**
 * This is in large based on the tutorial at learnopengl.com.
 */
GLRenderer::GLRenderer() {
    //Below arrays define 2 triangles that make up the groundfloat vertices[] = {
    float grnd[] = {
        // positions               // colors           // texture coords
        -10000.0f, 0.0f, -10000.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        10000.0f, 0.0f, -10000.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        10000.0f, 0.0f, 10000.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -10000.0f, 0.0f, 10000.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3,
    };

    groundShader_ = std::make_unique<Shader>(SHADER_DIR "vertex.glsl", SHADER_DIR "fragment.glsl");
    groundTexture_ = std::make_unique<Texture>(TEXTURE_DIR "grid.jpg");

    //Set up OpenGL objects
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(grnd), grnd, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Vertices array
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);

    //Color array
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Texture array
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void GLRenderer::render(const RendererPayload &payload) const {
    groundShader_->use();

    //Taken from directly from claude. Not gonna study these transformations (again!!!!)

    glm::vec3 eye(
        static_cast<float>(payload.east),
        static_cast<float>(payload.up), //altitude
        static_cast<float>(-payload.north)
    );

    glm::mat4 att(1.0f);
    att = glm::rotate(att, glm::radians(static_cast<float>(-payload.heading)), glm::vec3(0, 1, 0));
    att = glm::rotate(att, glm::radians(static_cast<float>(payload.pitch)),  glm::vec3(1, 0, 0));
    att = glm::rotate(att, glm::radians(static_cast<float>(payload.roll)),   glm::vec3(0, 0, -1));

    glm::vec3 forward = glm::vec3(att * glm::vec4(0, 0, -1, 0));
    glm::vec3 up = glm::vec3(att * glm::vec4(0, 1, 0, 0));

    glm::mat4 view = glm::lookAt(eye, eye + forward, up);

    groundShader_->setMat4("model", glm::mat4(1.0f));
    groundShader_->setMat4("view", view);
    groundShader_->setMat4("projection",
                           glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 20000.0f));
    groundShader_->setInt("groundTex", 0);

    groundTexture_->use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, static_cast<void *>(nullptr));
    glBindVertexArray(0);
}
