//
// Created by dezlow on 17.09.2021.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "Shader.h"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

unsigned int CreateVertexShader(const char* shaderSrc);
unsigned int CreateFragmentShader(const char* shaderSrc);
uint32_t CreateProgram(uint32_t vertexShaderID, uint32_t fragmentShaderID);
void CheckCompileErrors(uint32_t shader, const char* type);

void Shader::LoadFromSource(const char* vertexShaderSrc, const char* fragmentShaderSrc)
{
    unsigned int vertex, fragment;

    vertex = gl::CreateShader(gl::VERTEX_SHADER);
    gl::ShaderSource(vertex, 1, &vertexShaderSrc, nullptr);
    gl::CompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");

    fragment = gl::CreateShader(gl::FRAGMENT_SHADER);
    gl::ShaderSource(fragment, 1, &fragmentShaderSrc, nullptr);
    gl::CompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");

    mShaderID = gl::CreateProgram();
    gl::AttachShader(mShaderID, vertex);
    gl::AttachShader(mShaderID, fragment);
    gl::LinkProgram(mShaderID);
    CheckCompileErrors(mShaderID, "PROGRAM");

    gl::DeleteShader(vertex);
    gl::DeleteShader(fragment);
}

void Shader::LoadFromPath(const char* vertexShaderPath, const char* fragmentShaderPath)
{
    std::string vertexShaderSrc;
    std::string fragmentShaderSrc;

    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;

    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vertexShaderFile.open(vertexShaderPath);
        fragmentShaderFile.open(fragmentShaderPath);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexShaderSrc = vShaderStream.str();
        fragmentShaderSrc = fShaderStream.str();
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }

    unsigned int vertexShader = CreateVertexShader(vertexShaderSrc.c_str()),
                 fragmentShader = CreateFragmentShader(fragmentShaderSrc.c_str());

    mShaderID = CreateProgram(vertexShader, fragmentShader);

    gl::DeleteShader(vertexShader);
    gl::DeleteShader(fragmentShader);
}

void Shader::UnLoad() const
{
    gl::DeleteProgram(mShaderID);
}

GLint Shader::GetUniformLocation(const std::string& name) const
{
    if (mUniformLocationCache.find(name) != mUniformLocationCache.end())
        return mUniformLocationCache[name];

    GLint location = gl::GetUniformLocation(mShaderID, name.c_str());
    mUniformLocationCache[name] = location;
    return location;
}

unsigned int CreateVertexShader(const char* shaderSrc)
{
    uint32_t shaderID = gl::CreateShader(gl::VERTEX_SHADER);

    gl::ShaderSource(shaderID, 1, &shaderSrc, nullptr);
    gl::CompileShader(shaderID);
    CheckCompileErrors(shaderID, "VERTEX");

    return shaderID;
}

uint32_t CreateFragmentShader(const char* shaderSrc)
{
    uint32_t shaderID = gl::CreateShader(gl::FRAGMENT_SHADER);

    gl::ShaderSource(shaderID, 1, &shaderSrc, nullptr);
    gl::CompileShader(shaderID);
    CheckCompileErrors(shaderID, "FRAGMENT");

    return shaderID;
}

uint32_t CreateProgram(uint32_t vertexShaderID, uint32_t fragmentShaderID)
{
    uint32_t programID = gl::CreateProgram();

    gl::AttachShader(programID, vertexShaderID);
    gl::AttachShader(programID, fragmentShaderID);
    gl::LinkProgram(programID);
    CheckCompileErrors(programID, "PROGRAM");

    return programID;
}

void CheckCompileErrors(uint32_t shader, const char* type)
{
    int succes;
    char infoLog[512];

    if (type != "PROGRAM")
    {
        gl::GetShaderiv(shader, gl::COMPILE_STATUS, &succes);

        if (!succes)
        {
            gl::GetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cout << infoLog << std::endl;
        }
    }
    else
    {
        gl::GetProgramiv(shader, gl::LINK_STATUS, &succes);

        if (!succes)
        {
            gl::GetProgramInfoLog(shader, 512, nullptr, infoLog);
            std::cout << infoLog << std::endl;
        }
    }
}

template<>
void Shader::SetUniform<float>(const std::string& uniformName, const float& value)
{
    gl::Uniform1f(GetUniformLocation(uniformName), value);
}

template<>
void Shader::SetUniform<int>(const std::string& uniformName, const int& value)
{
    gl::Uniform1i(GetUniformLocation(uniformName), value);
}

template<>
void Shader::SetUniform<glm::vec3>(const std::string& uniformName, const glm::vec3& value)
{
    gl::Uniform3fv(GetUniformLocation(uniformName), 1, &value[0]);
}

template<>
void Shader::SetUniform<glm::mat4>(const std::string& uniformName, const glm::mat4& value)
{
    gl::UniformMatrix4fv(GetUniformLocation(uniformName), 1, gl::FALSE_, &value[0][0]);
}