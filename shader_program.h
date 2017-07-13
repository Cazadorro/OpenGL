#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <iostream>

class ShaderProgram {
public:
    unsigned int ID;

    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    ShaderProgram(const std::string &vertex_path, const std::string &fragment_path);
    ShaderProgram(const std::string &vertex_path, const std::string &fragment_path, const std::string &geometry_path);
    ~ShaderProgram();

    // activate the shader
    // ------------------------------------------------------------------------
    void use();

    // utility uniform functions

    void setUniform(const std::string &uniform_name, const bool value) const;

    void setUniform(const std::string &uniform_name, const int value) const;

    void setUniform(const std::string &uniform_name, const float value) const;

    void setUniform(const std::string &uniform_name, const glm::vec2& value) const;

    void setUniform(const std::string &uniform_name, const glm::vec3& value) const;

    void setUniform(const std::string &uniform_name, const glm::vec4& value) const;

    void setUniform(const std::string &uniform_name, const glm::mat2& value) const;

    void setUniform(const std::string &uniform_name, const glm::mat3& value) const;

    void setUniform(const std::string &uniform_name, const glm::mat4& value) const;

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors();
};

#endif