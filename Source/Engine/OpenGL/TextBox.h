//
// Created by dezlow on 22.10.2021.
//

#ifndef REBIRTH_TEXTBOX_H
#define REBIRTH_TEXTBOX_H


#include "Engine/Lua/LuaImage.h"

class TextBox
{
public:
    TextBox() {}
    ~TextBox() {}

    void Init(const std::string& pathToImg)
    {
        const char* vertexShaderSrc = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec2 aTexCoords;
            uniform mat4 uMVP;

            out vec2 TexCoords;

            void main()
            {
                TexCoords = aPos.xy;
                gl_Position = uMVP * vec4(aPos, 1.0);
            }
        )";

        const char* fragmentShaderSrc = R"(
            #version 330 core
            out vec4 FragColor;

            uniform sampler2D uTexture;

            uniform int uTextureWidth, uTextureHeight;

            in vec2 TexCoords;

            uniform float uTextureAlpha;

            void main()
            {
                vec4 Texture = texture2D(uTexture, vec2(TexCoords.x / uTextureWidth, TexCoords.y / uTextureHeight));
                if(Texture.a < 0.1)
                        discard;
                if (uTextureAlpha < Texture.a)
                    Texture.a = uTextureAlpha;
                FragColor = vec4(Texture.rgba);
            }
        )";

        mTextBoxImage = LuaImage(pathToImg);
        mTextBoxImage.GetTransition()->SetType(TransitionTypes::DISSOLVE);
        mTextBoxImage.GetShader()->LoadFromSource(vertexShaderSrc, fragmentShaderSrc);
        mTextBoxImage.GetTexture()->Load(pathToImg);

        mTextBoxImage.GetShader()->use();
        mTextBoxImage.GetShader()->SetUniform<int>("uTextureWidth", mTextBoxImage.GetTexture()->width);
        mTextBoxImage.GetShader()->SetUniform<int>("uTextureHeight", mTextBoxImage.GetTexture()->height);
    }

    LuaImage* GetImage() { return &mTextBoxImage; }

    void Update(const float& dt)
    {
        if (mTextBoxImage.GetCurrentAlpha() < 1.0f)
        {
            alpha += dt * 1.5f;
            mTextBoxImage.SetAlpha(alpha);
        }
    }
    float alpha = 0.0f;
private:
    LuaImage mTextBoxImage;
};


#endif //REBIRTH_TEXTBOX_H
