//
// Created by dezlow on 17.09.2021.
//

#include <iostream>
#include <fstream>
#include "Texture.h"
#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

Texture::Texture(const std::string& texturePath)
{
    int nrChannels;
    uint8_t* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        glGenTextures(1, &mTextureID);
        Bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        switch (nrChannels)
        {
        case 4:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            break;
        case 3:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        default:
            break;
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture!\n";
    }
    stbi_image_free(data);
}

void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, mTextureID);
}

void Texture::UnBind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
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
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

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
        glGenTextures(1, &mTextureID);
        Bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        switch (nrChannels)
        {
        case 4:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            break;
        case 3:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        default:
            break;
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture! Path: "  << path << '\n';
    }
    stbi_image_free(data);
}

void Texture::UnLoad()
{
    glDeleteTextures(1, &mTextureID);
}
