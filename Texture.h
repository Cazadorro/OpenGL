//
// Created by Shae Bolt on 10/1/2017.
//

#ifndef GLPROJECT_TEXTURE2DD_H
#define GLPROJECT_TEXTURE2DD_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
namespace gl{

    class Texture {
        GLenum m_target;
        GLuint m_handle;

#ifdef DEBUG
        bool m_bound = false;
#endif

    public:
        Texture(GLenum target, const std::string& file_path);
        explicit operator GLuint() const;
        void bind(GLenum target);
        void setParameter(GLenum name, GLfloat value);
        void setParameter(GLenum name, GLint value);
        void setParameter(GLenum name, const GLfloat* value);
        void setParameter(GLenum name, const GLint* value);
        void setParameterInt(GLenum name, const GLint* value);
        void setParameterInt(GLenum name, const GLuint* value);
    private:
        void generate();

    };
};



#endif //GLPROJECT_TEXTURE2DD_H
