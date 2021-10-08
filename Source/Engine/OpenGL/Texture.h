//
// Created by dezlow on 17.09.2021.
//

#ifndef REBIRTH_TEXTURE_H
#define REBIRTH_TEXTURE_H


#include <cstdint>

class Texture
{
public:
    Texture() = default;
    ~Texture() = default;

    explicit Texture(const std::string& texturePath);

    void Bind() const;
    void UnBind() const;

    int width, height;

    void Load(const std::string& path);
    void UnLoad();
private:
    uint32_t mTextureID;
};


#endif //REBIRTH_TEXTURE_H
