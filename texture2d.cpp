//
// Created by Shae Bolt on 7/12/2017.
//

#include "texture2d.h"

#include "stb_image.h"
#include <iostream>

Texture2D::Texture2D(const std::string &texture_path, const TextureViewParams &texture_params) {
    glGenTextures(1, &m_gpu_texture_handle);
    bind();
    setParameters(texture_params);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load(texture_path.c_str(),
                                    &width, &height, &nrChannels, 0);
    if (data) {
        GLenum channels = GL_RGBA;
        if(nrChannels == 3){
            channels = GL_RGB;
        }
        setData(data, {width, height, GL_RGB, channels});
    } else {
        std::cerr << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

}

Texture2D::Texture2D(const unsigned char *data, const TextureSizeParams &size_params,
                     const TextureViewParams &texture_params) {
    glGenTextures(1, &m_gpu_texture_handle);
    bind();
    setParameters(texture_params);
    setData(data, TextureSizeParams());
}

void Texture2D::setData(const unsigned char *data, const TextureSizeParams &size_params) {
    // load image, create texture and generate mipmaps
    glTexImage2D(GL_TEXTURE_2D, 0, size_params.gl_channel_format, size_params.width, size_params.height, 0,
                 size_params.data_channel_format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture2D::bind() {
    glBindTexture(GL_TEXTURE_2D, m_gpu_texture_handle);
}

void Texture2D::activate(const GLenum bind_texture_index) {
    glActiveTexture(bind_texture_index);
    bind();
}

void Texture2D::setParameter(const GLenum parameter, const GLint value) {
    glTexParameteri(GL_TEXTURE_2D, parameter, value);
}

void Texture2D::setParameters(const TextureViewParams &texture_params) {
    setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
    setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


Texture2D::~Texture2D() {
}

