#pragma once

#include <string>
#include <glm/glm.hpp>

namespace AnimView {

// Wraps an OpenGL shader program compiled from vertex and fragment source strings.
// Use Bind() before issuing draw calls, Unbind() when done.
class Shader {
public:
    Shader(const std::string& vertexSource, const std::string& fragmentSource);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    // Bind / unbind the shader program
    void Bind()   const;
    void Unbind() const;

    // Uniform setters
    void SetInt  (const std::string& name, int value)              const;
    void SetFloat(const std::string& name, float value)            const;
    void SetVec2 (const std::string& name, const glm::vec2& value) const;
    void SetVec3 (const std::string& name, const glm::vec3& value) const;
    void SetVec4 (const std::string& name, const glm::vec4& value) const;
    void SetMat4 (const std::string& name, const glm::mat4& value) const;

    unsigned int GetProgramID() const { return m_ProgramID; }

private:
    static unsigned int CompileShader(unsigned int type, const std::string& source);

private:
    unsigned int m_ProgramID = 0;
};

} // namespace AnimView
