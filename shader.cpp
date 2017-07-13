//
// Created by Shae Bolt on 7/12/2017.
//

#include "shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

const std::unordered_map<GLenum, std::string> Shader::shader_enum_string = {
        {GL_VERTEX_SHADER, "VERTEX"},
        {GL_FRAGMENT_SHADER, "FRAGMENT"},
        {GL_GEOMETRY_SHADER, "GEOMETRY"}
};

Shader::Shader(const GLenum shader_type, const std::string &shader_path) {
    m_valid = true;
    // 1. retrieve the vertex/fragment source code from filePath
    std::string shader_code;
    std::ifstream shader_file_stream;
    // ensure ifstream objects can throw exceptions:
    shader_file_stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        shader_file_stream.open(shader_path);
        std::stringstream shader_string_stream;
        // read file's buffer contents into streams
        shader_string_stream << shader_file_stream.rdbuf();
        // close file handlers
        shader_file_stream.close();
        // convert stream into string
        shader_code = shader_string_stream.str();
    } catch (std::ifstream::failure e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        m_valid = false;
    }
    const char* shader_code_cstring = shader_code.c_str();

    m_gpu_shader_handle = glCreateShader(shader_type);
    glShaderSource(m_gpu_shader_handle, 1, &shader_code_cstring, NULL);
    glCompileShader(m_gpu_shader_handle);

    checkCompileErrors();
}

bool Shader::isValid() const {
    return m_valid;
}

GLenum Shader::type() const {
    return m_type;
}

Shader::operator GLuint() const {
    return m_gpu_shader_handle;
}

void Shader::checkCompileErrors() {
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(m_gpu_shader_handle, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(m_gpu_shader_handle, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << shader_enum_string.at(type()) << "\n" << infoLog
                  << "\n -- --------------------------------------------------- -- " << std::endl;
        m_valid = false;
    }
}

Shader::~Shader() {
    glDeleteShader(m_gpu_shader_handle);
}
