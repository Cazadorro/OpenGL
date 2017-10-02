//
// Created by Shae Bolt on 10/1/2017.
//

#ifndef GLPROJECT_ERRORS_H
#define GLPROJECT_ERRORS_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
namespace gl{
    void clear();
    GLenum getNext();
    GLenum getLast();
    std::vector<GLenum> getAll();
}



#endif //GLPROJECT_ERRORS_H
