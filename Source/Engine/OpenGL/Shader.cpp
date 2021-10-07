//
// Created by dezlow on 17.09.2021.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "Shader.h"
#include "glm/glm.hpp"

unsigned int CreateVertexShader(const char* shaderSrc);
unsigned int CreateFragmentShader(const char* shaderSrc);
uint32_t CreateProgram(const uint32_t& vertexShaderID, const uint32_t& fragmentShaderID);
void CheckCompileErrors(const uint32_t& shader, const char* type);

void Shader::LoadFromSource(const char* vertexShaderSrc, const char* fragmentShaderSrc)
{
    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShaderSrc, nullptr);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentShaderSrc, nullptr);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");

    mShaderID = glCreateProgram();
    glAttachShader(mShaderID, vertex);
    glAttachShader(mShaderID, fragment);
    glLinkProgram(mShaderID);
    CheckCompileErrors(mShaderID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
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

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::UnLoad() const
{
    glDeleteProgram(mShaderID);
}

unsigned int CreateVertexShader(const char* shaderSrc)
{
    uint32_t shaderID = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(shaderID, 1, &shaderSrc, nullptr);
    glCompileShader(shaderID);
    CheckCompileErrors(shaderID, "VERTEX");

    return shaderID;
}

uint32_t CreateFragmentShader(const char* shaderSrc)
{
    uint32_t shaderID = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(shaderID, 1, &shaderSrc, nullptr);
    glCompileShader(shaderID);
    CheckCompileErrors(shaderID, "FRAGMENT");

    return shaderID;
}

uint32_t CreateProgram(const uint32_t& vertexShaderID, const uint32_t& fragmentShaderID)
{
    uint32_t programID = glCreateProgram();

    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);
    CheckCompileErrors(programID, "PROGRAM");

    return programID;
}

void CheckCompileErrors(const uint32_t& shader, const char* type)
{
    int succes;
    char infoLog[512];

    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);

        if (!succes)
        {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cout << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &succes);

        if (!succes)
        {
            glGetProgramInfoLog(shader, 512, nullptr, infoLog);
            std::cout << infoLog << std::endl;
        }
    }
}

template<>
void Shader::SetUniform<float>(const std::string& uniformName, const float& value) const
{
    glUniform1f(glGetUniformLocation(mShaderID, uniformName.c_str()), value);
}

template<>
void Shader::SetUniform<int>(const std::string& uniformName, const int& value) const
{
    glUniform1i(glGetUniformLocation(mShaderID, uniformName.c_str()), value);
}

template<>
void Shader::SetUniform<glm::vec3>(const std::string& uniformName, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(mShaderID, uniformName.c_str()), 1, &value[0]);
}

template<>
void Shader::SetUniform<glm::mat4>(const std::string& uniformName, const glm::mat4& value) const
{
    glUniformMatrix4fv(glGetUniformLocation(mShaderID, uniformName.c_str()), 1, GL_FALSE, &value[0][0]);
}