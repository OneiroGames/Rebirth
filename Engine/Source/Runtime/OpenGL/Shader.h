//
// Created by dezlow on 17.09.2021.
//

#ifndef REBIRTH_SHADER_H
#define REBIRTH_SHADER_H

#include "glad/glad.h"

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
private:
    mutable std::unordered_map<std::string, GLint> mUniformLocationCache;
    uint32_t mShaderID{};

    GLint GetUniformLocation(const std::string& name) const;
};


#endif //REBIRTH_SHADER_H
