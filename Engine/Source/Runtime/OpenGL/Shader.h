//
// Created by Dezlow on 17.09.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#ifndef REBIRTH_SHADER_H
#define REBIRTH_SHADER_H

#include "OpenGL/ogl4.5.hpp"

#include <string>
#include <unordered_map>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Shader
{
public:
    Shader() = default;
    ~Shader() = default;

    void LoadFromPath(const char* vertexShaderPath, const char* fragmentShaderPath);
    void LoadFromSource(const char* vertexShaderSrc, const char* fragmentShaderSrc);
    inline void use() const { gl::UseProgram(mShaderID); }

    void UnLoad() const;

    void SetUniform(const char* uname, float value) {
        gl::Uniform1f(GetUniformLocation(uname), value);
    }

    void SetUniform(const char* uname, int value) {
        gl::Uniform1i(GetUniformLocation(uname), value);
    }

    void SetUniform(const char* uname, const glm::vec3& value) {
        gl::Uniform3fv(GetUniformLocation(uname), 1, &value[0]);
    }

    void SetUniform(const char* uname, const glm::mat4& value) {
        gl::UniformMatrix4fv(GetUniformLocation(uname), 1, gl::FALSE_, &value[0][0]);
    }
private:
    GLint GetUniformLocation(const char* name) const;

    mutable std::unordered_map<const char*, GLint> mUniformLocationCache;
    uint32_t mShaderID{};
};


#endif //REBIRTH_SHADER_H
