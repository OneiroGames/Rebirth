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
    explicit Texture(const std::string& texturePath);
    ~Texture();

    void Bind() const;
    void UnBind() const;

    void Load(const std::string& path);

    void UnLoad();

    [[nodiscard]] int GetWidth() const { return mTextureWidth; }
    [[nodiscard]] int GetHeight() const { return mTextureHeight; }
private:
    int mTextureWidth{}, mTextureHeight{};
    uint32_t mTextureID{};
};


#endif //REBIRTH_TEXTURE_H
