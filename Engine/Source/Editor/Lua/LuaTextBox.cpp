//
// Created by Dezlow on 22.10.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#include "LuaTextBox.h"

void LuaTextBox::Init(const std::string& pathToImg)
{
    const char* LTBVertexShaderSrc = R"(
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

    const char* LTBFragmentShaderSrc = R"(
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
                if (uTextureAlpha <= Texture.a)
                    Texture.a = uTextureAlpha;
                FragColor = vec4(Texture.rgba);
            }
        )";

    mTextBoxImage = LuaImage(pathToImg);
    mTextBoxImage.GetTransition()->SetType(TransitionTypes::DISSOLVE);
    mTextBoxImage.GetShader()->LoadFromSource(LTBVertexShaderSrc, LTBFragmentShaderSrc);
    mTextBoxImage.GetTexture()->Load(pathToImg);

    mTextBoxImage.GetShader()->use();
    mTextBoxImage.GetShader()->SetUniform("uTextureWidth", mTextBoxImage.GetTexture()->GetWidth());
    mTextBoxImage.GetShader()->SetUniform("uTextureHeight", mTextBoxImage.GetTexture()->GetHeight());
}

void LuaTextBox::Update(const float& dt)
{
    if (mReDissolve && !mDissolve)
    {
        mCurrentReAlpha -= 1.5f * dt;
        mTextBoxImage.SetAlpha(mCurrentReAlpha);

        mReDissolve = true;

        if (mTextBoxImage.GetCurrentAlpha() <= 0.0f)
        {
            mCurrentReAlpha = 1.0f;
            mCurrentAlpha = 0.0f;
            mReDissolve = false;
        }
    }
    else if (mTextBoxImage.GetCurrentAlpha() <= 1.0f)
    {
        mCurrentAlpha += dt * 1.5f;
        mTextBoxImage.SetAlpha(mCurrentAlpha);

        mDissolve = true;

        if (mTextBoxImage.GetCurrentAlpha() > 1.0f)
        {
            mCurrentAlpha = 0.0f;
            mCurrentReAlpha = 1.0f;
            mDissolve = false;
        }
    }
}

void LuaTextBox::Draw(const glm::mat4& MVP)
{
    mTextBoxImage.GetShader()->use();
    mTextBoxImage.GetShader()->SetUniform("uMVP", MVP);
    mTextBoxImage.GetTexture()->Bind();

    gl::DrawArrays(gl::TRIANGLES, 0, 6);
}

void LuaTextBox::SetDissolveEnabled()
{
    mDissolve = true;
    mReDissolve = false;
    mCurrentAlpha = 0.0f;
}

void LuaTextBox::SetReDissolveEnabled()
{
    mDissolve = false;
    mReDissolve = true;
    mCurrentReAlpha = 1.0f;
}
