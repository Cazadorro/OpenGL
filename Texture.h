//
// Created by Shae Bolt on 10/1/2017.
//

#ifndef GLPROJECT_TEXTURE2DD_H
#define GLPROJECT_TEXTURE2DD_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "stb_image.h"
namespace gl{



    class ImageData{
    private:
        int m_width;
        int m_height;
        int m_channels;
        unsigned char * m_data;
    public:
        ImageData();
        ImageData(unsigned char * data, int width, int height, int channels);
        friend void load(const std::string& file_path, ImageData& image, int out_channels = 0);
    };

    void load(const std::string& file_path, ImageData& image, int out_channels = 0){
        int width, height, channels;
        unsigned char *data = stbi_load(file_path.c_str(), &width, &height, &channels, out_channels);
        image.m_width = width;
        image.m_height = height;
        image.m_channels = channels;
        image.m_data = data;
    }

    class Texture {
        GLenum m_target;
        GLuint m_handle;

#ifdef DEBUG
        bool m_bound = false;
#endif
    public:
        Texture(GLenum target, const std::string& file_path);
        static Texture readFromImage(GLenum target, const std::string& file_path);
        explicit operator GLuint() const;
        void bind(GLenum target);
        void setParameter(GLenum name, GLfloat value);
        void setParameter(GLenum name, GLint value);
        void setParameter(GLenum name, const GLfloat* value);
        void setParameter(GLenum name, const GLint* value);
        void setParameterInt(GLenum name, const GLint* value);
        void setParameterInt(GLenum name, const GLuint* value);
        //todo get parameter, only works for vector, but we should be able to get anyway.
        //glGetTexParameterfv
    private:
        void generate();

    };
};



#endif //GLPROJECT_TEXTURE2DD_H
