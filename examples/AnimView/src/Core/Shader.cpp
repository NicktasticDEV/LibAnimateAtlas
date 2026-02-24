#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <cassert>
#include <stdexcept>
#include <string>

namespace AnimView {

// ---------------------------------------------------------------------------
// Internal helper
// ---------------------------------------------------------------------------
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char log[1024];
        glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
        glDeleteShader(shader);
        throw std::runtime_error(
            std::string(type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") +
            " shader compilation failed:\n" + log);
    }

    return shader;
}

// ---------------------------------------------------------------------------
// Constructor / destructor
// ---------------------------------------------------------------------------
Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
{
    unsigned int vert = CompileShader(GL_VERTEX_SHADER,   vertexSource);
    unsigned int frag = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

    m_ProgramID = glCreateProgram();
    glAttachShader(m_ProgramID, vert);
    glAttachShader(m_ProgramID, frag);
    glLinkProgram(m_ProgramID);

    glDeleteShader(vert);
    glDeleteShader(frag);

    int success = 0;
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
    if (!success)
    {
        char log[1024];
        glGetProgramInfoLog(m_ProgramID, sizeof(log), nullptr, log);
        glDeleteProgram(m_ProgramID);
        m_ProgramID = 0;
        throw std::runtime_error(std::string("Shader program linking failed:\n") + log);
    }
}

Shader::~Shader()
{
    if (m_ProgramID)
    {
        glDeleteProgram(m_ProgramID);
        m_ProgramID = 0;
    }
}

// ---------------------------------------------------------------------------
// Bind / Unbind
// ---------------------------------------------------------------------------
void Shader::Bind() const
{
    glUseProgram(m_ProgramID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

// ---------------------------------------------------------------------------
// Uniform setters
// ---------------------------------------------------------------------------
void Shader::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(m_ProgramID, name.c_str()), value);
}

void Shader::SetVec2(const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetMat4(const std::string& name, const glm::mat4& value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

} // namespace AnimView
