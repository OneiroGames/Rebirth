//
// Created by dezlow on 17.09.2021.
//

#ifndef REBIRTH_SHADER_H
#define REBIRTH_SHADER_H

#include "glad/glad.h"
#include "glm/glm.hpp"

#include <string>
#include <unordered_map>

class Shader
{
public:
    Shader() = default;
    ~Shader() = default;

    void LoadFromPath(const char* vertexShaderPath, const char* fragmentShaderPath);
    void LoadFromSource(const char* vertexShaderSrc, const char* fragmentShaderSrc);
    inline void use() const { glUseProgram(mShaderID); }

    void UnLoad() const;

    template<class T>
    void SetUniform(const std::string& uniformName, const T& value) {}

#ifdef _MSC_BUILD
    template<>
    void Shader::SetUniform<float>(const std::string& uniformName, const float& value)
    {
        glUniform1f(glGetUniformLocation(mShaderID, uniformName.c_str()), value);
    }

    template<>
    void Shader::SetUniform<int>(const std::string& uniformName, const int& value)
    {
        glUniform1i(GetUniformLocation(uniformName), value);
    }

    template<>
    void Shader::SetUniform<glm::vec3>(const std::string& uniformName, const glm::vec3& value)
    {
        glUniform3fv(GetUniformLocation(uniformName), 1, &value[0]);
    }

    template<>
    void Shader::SetUniform<glm::mat4>(const std::string& uniformName, const glm::mat4& value)
    {
        glUniformMatrix4fv(GetUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]);
    }
#endif
private:
    mutable std::unordered_map<std::string, GLint> mUniformLocationCache;
    uint32_t mShaderID{};

    GLint GetUniformLocation(const std::string& name) const;
};


#endif //REBIRTH_SHADER_H
