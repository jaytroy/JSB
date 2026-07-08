//
// Created by jay on 7/8/26.
//
#include "GLRenderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <memory>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    //Set up OpenGL objects
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(grnd), grnd, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    //Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //Can this be moved out into its own class?
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(SHADER_DIR "grid.jpg", &width, &height, &nrChannels, 0);
    if (!data) {
        throw std::runtime_error(std::string("Failed to load ground texture from ") + SHADER_DIR "grid.jpg");
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void GLRenderer::render(std::vector<double> &payload) {
    groundShader_->use();

    //Taken from directly from claude. Not gonna study these transformations (again!!!!)

    // payload: [0]=time [1]=north [2]=east [3]=up [4]=heading [5]=airspeed
    //          [6]=throttle [7]=rpm [8]=pitch [9]=roll [10]=brake
    double north = payload[1];
    double east = payload[2];
    double alt = payload[3];
    double heading = payload[4];
    double pitch = payload[8];
    double roll = payload[9];

    // NED-ish → GL (Y up): east→X, altitude→Y, north→-Z
    glm::vec3 eye(
        (float) east,
        (float) alt,
        (float) -north
    );

    // Aircraft attitude → camera orientation (yaw, then pitch, then roll)
    glm::mat4 att(1.0f);
    att = glm::rotate(att, glm::radians((float)heading), glm::vec3(0, 1, 0));
    att = glm::rotate(att, glm::radians((float)pitch),  glm::vec3(1, 0, 0));
    att = glm::rotate(att, glm::radians((float)roll),   glm::vec3(0, 0, 1));

    glm::vec3 forward = glm::vec3(att * glm::vec4(0, 0, -1, 0));
    glm::vec3 up = glm::vec3(att * glm::vec4(0, 1, 0, 0));

    glm::mat4 view = glm::lookAt(eye, eye + forward, up);

    groundShader_->setMat4("model", glm::mat4(1.0f));
    groundShader_->setMat4("view", view);
    groundShader_->setMat4("projection",
                           glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 20000.0f));
    groundShader_->setInt("groundTex", 0);

    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *) 0);
    glBindVertexArray(0);
}
