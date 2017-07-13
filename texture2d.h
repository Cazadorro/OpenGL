//
// Created by Shae Bolt on 7/12/2017.
//

#ifndef GLPROJECT_TEXTURE_H
#define GLPROJECT_TEXTURE_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>


struct TextureViewParams {
    GLint texture_wrap_s;
    GLint texture_wrap_t;
    GLint texture_min_filter;
    GLint texture_mag_filter;
};

struct TextureSizeParams {
    GLsizei width;
    GLsizei height;
    GLenum gl_channel_format;
    GLenum data_channel_format;
};

class Texture2D {
    GLuint m_gpu_texture_handle;
public:
    Texture2D(const std::string &texture_path, const TextureViewParams &texture_params);

    Texture2D(const unsigned char *data, const TextureSizeParams &size_params, const TextureViewParams &texture_params);

    void setData(const unsigned char *data, const TextureSizeParams &size_params);

    void bind();

    void activate(const GLenum bind_texture_index);

    void setParameter(const GLenum parameter, const GLint value);

    void setParameters(const TextureViewParams &texture_params);

    ~Texture2D();
};


#endif //GLPROJECT_TEXTURE_H
