//
// Created by dezlow on 17.09.2021.
//

#include <iostream>
#include "Texture.h"
#include "OpenGL/ogl4.5.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

Texture::Texture(const std::string& texturePath)
{
    int nrChannels;
    uint8_t* data = stbi_load(texturePath.c_str(), &mTextureWidth, &mTextureHeight, &nrChannels, 0);

    if (data)
    {
        gl::GenTextures(1, &mTextureID);
        Bind();
        gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::CLAMP_TO_EDGE);
        gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::CLAMP_TO_EDGE);
        gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR_MIPMAP_LINEAR);
        gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR_MIPMAP_LINEAR);
        switch (nrChannels)
        {
        case 4:
            gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGBA, mTextureWidth, mTextureWidth, 0, gl::RGBA, gl::UNSIGNED_BYTE, data);
            break;
        case 3:
            gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGB, mTextureWidth, mTextureWidth, 0, gl::RGB, gl::UNSIGNED_BYTE, data);
            break;
        default:
            break;
        }
        gl::GenerateMipmap(gl::TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture!\n";
    }
    stbi_image_free(data);
}

void Texture::Bind() const
{
    gl::BindTexture(gl::TEXTURE_2D, mTextureID);
}

void Texture::UnBind() const
{
    gl::BindTexture(gl::TEXTURE_2D, 0);
}

/*#include <algorithm>
#include <sstream>
#include <iomanip>

std::string ToHex(const std::string& s, bool upper_case /* = true )
{
    std::ostringstream ret;

    for (std::string::size_type i = 0; i < s.length(); ++i)
        ret << std::hex << std::setfill('0') << std::setw(2) << (upper_case ? std::uppercase : std::nouppercase) << (int)s[i];

    return ret.str();
}*/

void Texture::Load(const std::string& path)
{
    int nrChannels;
    unsigned char* data = stbi_load(path.c_str(), &mTextureWidth, &mTextureHeight, &nrChannels, 0);

    /*std::ifstream f(path);
    std::ofstream file(path + "c");
    file << f.rdbuf();
    f.close();
    f.open(path + "c");
    file.close();
    file.open(path + "cc");

    std::string t;

    while (getline(f, t))
    {
        std::reverse(t.begin(), t.end());
        ToHex(t, false);
        file << std::hex << t + "\n";
    }
    file.close();
    f.close();*/

    if (data)
    {
        gl::GenTextures(1, &mTextureID);
        Bind();
        gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::CLAMP_TO_EDGE);
        gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::CLAMP_TO_EDGE);
        gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::NEAREST);
        gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
        switch (nrChannels)
        {
        case 4:
            gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGBA, mTextureWidth, mTextureHeight, 0, gl::RGBA, gl::UNSIGNED_BYTE, data);
            break;
        case 3:
            gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGB, mTextureWidth, mTextureHeight, 0, gl::RGB, gl::UNSIGNED_BYTE, data);
            break;
        default:
            break;
        }
        gl::GenerateMipmap(gl::TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture! Path: " << path << '\n';
    }
    stbi_image_free(data);
}

void Texture::UnLoad()
{
    gl::DeleteTextures(1, &mTextureID);
}

Texture::~Texture()
{
    gl::DeleteTextures(1, &mTextureID);
}
