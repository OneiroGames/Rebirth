//
// Created by dezlow on 17.09.2021.
//

#ifndef REBIRTH_SHADER_H
#define REBIRTH_SHADER_H

#include "OpenGL/ogl4.5.hpp"

#include <string>
#include <unordered_map>

class Shader
{
public:
    Shader() = default;
    ~Shader() = default;

    void LoadFromPath(const char* vertexShaderPath, const char* fragmentShaderPath);
    void LoadFromSource(const char* vertexShaderSrc, const char* fragmentShaderSrc);
    inline void use() const { gl::UseProgram(mShaderID); }

    void UnLoad() const;

    template<class T>
    void SetUniform(const std::string& uniformName, const T& value) {}
private:
    GLint GetUniformLocation(const std::string& name) const;

    mutable std::unordered_map<std::string, GLint> mUniformLocationCache;
    uint32_t mShaderID{};
};


#endif //REBIRTH_SHADER_H
