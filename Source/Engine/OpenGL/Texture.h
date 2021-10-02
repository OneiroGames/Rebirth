//
// Created by dezlow on 17.09.2021.
//

#ifndef REBIRTH_TEXTURE_H
#define REBIRTH_TEXTURE_H

class Texture
{
public:
    Texture();
    explicit Texture(const char* texturePath);

    ~Texture();

    void Bind() const;
    void UnBind() const;
    int width, height;

    void Load(const char* path);
    void UnLoad();
private:
    unsigned int mTextureID;
};


#endif //REBIRTH_TEXTURE_H
