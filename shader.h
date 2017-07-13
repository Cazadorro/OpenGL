//
// Created by Shae Bolt on 7/12/2017.
//

#ifndef GLPROJECT_SHADER_H
#define GLPROJECT_SHADER_H
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <unordered_map>

class Shader {
    GLuint m_gpu_shader_handle;
    GLenum m_type;
    bool m_valid = false;
    static const std::unordered_map<GLenum, std::string> shader_enum_string;
public:
    Shader(const GLenum shader_type, const std::string& shader_path);
    bool isValid()const;
    GLenum type()const;
    operator GLuint() const;
    ~Shader();
private:
    void checkCompileErrors();
};


#endif //GLPROJECT_SHADER_H
