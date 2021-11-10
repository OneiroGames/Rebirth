//
// Created by dezlow on 22.10.2021.
//

#include "LuaTextBox.h"

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

void LuaTextBox::Init(const std::string& pathToImg)
{
    mTextBoxSprite = LuaSprite(pathToImg);
    mTextBoxSprite.GetTransition()->SetType(TransitionTypes::DISSOLVE);
    mTextBoxSprite.GetShader()->LoadFromSource(LTBVertexShaderSrc, LTBFragmentShaderSrc);
    mTextBoxSprite.GetTexture()->Load(pathToImg);

    mTextBoxSprite.GetShader()->use();
    mTextBoxSprite.GetShader()->SetUniform<int>("uTextureWidth", mTextBoxSprite.GetTexture()->width);
    mTextBoxSprite.GetShader()->SetUniform<int>("uTextureHeight", mTextBoxSprite.GetTexture()->height);
}

void LuaTextBox::Update(const float& dt)
{
    if (mReDissolve && !mDissolve)
    {
        mCurrentReAlpha -= 1.5f * dt;
        mTextBoxSprite.SetAlpha(mCurrentReAlpha);

        mReDissolve = true;

        if (mTextBoxSprite.GetCurrentAlpha() <= 0.0f)
        {
            mCurrentReAlpha = 1.0f;
            mCurrentAlpha = 0.0f;
            mReDissolve = false;
        }
    }
    else if (mTextBoxSprite.GetCurrentAlpha() <= 1.0f)
    {
        mCurrentAlpha += dt * 1.5f;
        mTextBoxSprite.SetAlpha(mCurrentAlpha);

        mDissolve = true;

        if (mTextBoxSprite.GetCurrentAlpha() > 1.0f)
        {
            mCurrentAlpha = 0.0f;
            mCurrentReAlpha = 1.0f;
            mDissolve = false;
        }
    }
}

void LuaTextBox::Draw(glm::mat4& MVP)
{
    mTextBoxSprite.GetShader()->use();
    mTextBoxSprite.GetShader()->SetUniform<glm::mat4>("uMVP", MVP);
    mTextBoxSprite.GetTexture()->Bind();

    glDrawArrays(GL_TRIANGLES, 0, 6);
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
