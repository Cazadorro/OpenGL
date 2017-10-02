//
// Created by Shae Bolt on 10/1/2017.
//

#include "errors.h"

namespace gl{
    void clear() {
        while(glGetError() != GL_NO_ERROR){};
    }

    GLenum getLast() {
        GLenum last_error = glGetError();
        GLenum next_error;
        while((next_error = glGetError()) != GL_NO_ERROR){
            last_error = next_error;
        }
        return last_error;
    }

    GLenum getNext() {
        return glGetError();
    }

    std::vector<GLenum> getAll() {
        std::vector<GLenum> errors;
        GLenum next_error;
        while((next_error = glGetError()) != GL_NO_ERROR){
            errors.push_back(next_error);
        }
        return errors;
    }
}