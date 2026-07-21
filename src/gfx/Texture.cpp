//
// Created by jay on 7/20/26.
//

#include "Texture.h"

#include <stdexcept>
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_image.h"

Texture::Texture(const char *texturePath) {
    //Can this be moved out into its own class?
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(TEXTURE_DIR "grid.jpg", &width, &height, &nrChannels, 0);
    if (!data) {
        throw std::runtime_error(std::string("Failed to load ground texture from ") + texturePath);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

void Texture::use() {
    glBindTexture(GL_TEXTURE_2D, texture);
}