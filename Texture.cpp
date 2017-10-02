//
// Created by Shae Bolt on 10/1/2017.
//

#include "Texture.h"

namespace gl{

    Texture::Texture(GLenum target, const std::string &file_path) {
        bind(target);
    }

    Texture::operator GLuint() const {
        return m_handle;
    }

    void Texture::generate() {
        glGenTextures(1, &m_handle);
    }

    void Texture::bind(GLenum target) {
#ifdef DEBUG
        m_bound = true;
#endif
        m_target = target;
        glBindTexture(target, m_handle);
    }

    void Texture::setParameter(GLenum name, GLfloat value) {
        glTexParameterf(m_target, name, value);
    }

    void Texture::setParameter(GLenum name, GLint value) {
        glTexParameteri(m_target, name, value);
    }

    void Texture::setParameter(GLenum name, const GLfloat *value) {
        glTexParameterfv(m_target, name, value);
    }

    void Texture::setParameter(GLenum name, const GLint *value) {
        glTexParameteriv(m_target, name, value);
    }

    void Texture::setParameterInt(GLenum name, const GLint *value) {
        glTexParameterIiv(m_target, name, value);
    }

    void Texture::setParameterInt(GLenum name, const GLuint *value) {
        glTexParameterIuiv(m_target, name, value);
    }


}
