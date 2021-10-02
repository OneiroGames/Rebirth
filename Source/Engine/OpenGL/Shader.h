//
// Created by dezlow on 17.09.2021.
//

#ifndef REBIRTH_SHADER_H
#define REBIRTH_SHADER_H

#include "glad/glad.h"

class Shader
{
public:
    Shader() : mShaderID(0) {}
    ~Shader() = default;

    void LoadFromPath(const char* vertexShaderPath, const char* fragmentShaderPath);
    void LoadFromSource(const char* vertexShaderSrc, const char* fragmentShaderSrc);
    inline void use() const { glUseProgram(mShaderID); }

    void UnLoad();

    template<class T>
    void SetUniform(const char* uniformName, const T value) const {}
private:
    unsigned int mShaderID;
};


#endif //REBIRTH_SHADER_H
