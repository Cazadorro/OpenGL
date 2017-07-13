//
// Created by Shae Bolt on 7/11/2017.
//

#include "shader_program.h"
#include "shader.h"


ShaderProgram::ShaderProgram(const std::string &vertex_path, const std::string &fragment_path) {
// 1. retrieve the vertex/fragment source code from filePath
    Shader vertex_shader(GL_VERTEX_SHADER, vertex_path);
    Shader fragment_shader(GL_FRAGMENT_SHADER, fragment_path);

    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex_shader);
    glAttachShader(ID, fragment_shader);
    glLinkProgram(ID);
    checkCompileErrors();
    // delete the shaders as they're linked into our program now and no longer necessary
    // RAII now handles this! :)
}

ShaderProgram::ShaderProgram(const std::string &vertex_path, const std::string &fragment_path,
                             const std::string &geometry_path) {
    // 1. retrieve the vertex/fragment source code from filePath
    Shader vertex_shader(GL_VERTEX_SHADER, vertex_path);
    Shader fragment_shader(GL_FRAGMENT_SHADER, fragment_path);
    Shader geometry_shader(GL_GEOMETRY_SHADER, geometry_path);
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex_shader);
    glAttachShader(ID, fragment_shader);
    glAttachShader(ID, geometry_shader);
    glLinkProgram(ID);
    checkCompileErrors();
    // delete the shaders as they're linked into our program now and no longer necessary
    // RAII now handles this! :)
}

void ShaderProgram::use() {
    glUseProgram(ID);
}

//template<typename T>
//in case explict cast is required?
//void setUniform(const std::string &uniform_name, const bool value);

void ShaderProgram::setUniform(const std::string &uniform_name, const bool value) const {
    glUniform1i(glGetUniformLocation(ID, uniform_name.c_str()), static_cast<int>(value));
}

void ShaderProgram::setUniform(const std::string &uniform_name, const int value) const {
    glUniform1i(glGetUniformLocation(ID, uniform_name.c_str()), value);
}

void ShaderProgram::setUniform(const std::string &uniform_name, const float value) const {
    glUniform1f(glGetUniformLocation(ID, uniform_name.c_str()), value);
}

void ShaderProgram::setUniform(const std::string &uniform_name, const glm::vec2 &value) const {
    glUniform2fv(glGetUniformLocation(ID, uniform_name.c_str()), 1, &value[0]);
}

void ShaderProgram::setUniform(const std::string &uniform_name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(ID, uniform_name.c_str()), 1, &value[0]);
}

void ShaderProgram::setUniform(const std::string &uniform_name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(ID, uniform_name.c_str()), 1, &value[0]);
}

void ShaderProgram::setUniform(const std::string &uniform_name, const glm::mat2 &value) const {
    glUniformMatrix2fv(glGetUniformLocation(ID, uniform_name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::setUniform(const std::string &uniform_name, const glm::mat3 &value) const {
    glUniformMatrix3fv(glGetUniformLocation(ID, uniform_name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::setUniform(const std::string &uniform_name, const glm::mat4 &value) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, uniform_name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::checkCompileErrors() {
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 1024, NULL, infoLog);
        std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: PROGRAM" << "\n" << infoLog
                  << "\n -- --------------------------------------------------- -- " << std::endl;
    }
}