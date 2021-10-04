//
// Created by dezlow on 01.10.2021.
//

#ifndef REBIRTH_TEXT_H
#define REBIRTH_TEXT_H

#include "glad/glad.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <map>
#include <utility>

#include "ft2build.h"
#include FT_FREETYPE_H

struct Character {
    unsigned int TextureID;
    glm::ivec2   Size;
    glm::ivec2   Bearing;
    unsigned int Advance;
};

class Text
{
public:
    Text() = default;

    void Init(const char* fontPath, unsigned int charsSize = 40);

    void Render(glm::mat4 MVP, float x, float y);
    void SetString(const std::string& text) { mText = text; }
    void DisplayNextChar();
    bool isShowAllText() { return mTextToRender.size() == mText.size(); }
    void DisplayAllText() { mTextToRender = mText; mTextCurrentIterator = mText.size(); }
    void ClearTextToRender() { mTextToRender.clear(); mTextCurrentIterator = 0; }
private:
    void InitFreeType(FT_Library* ft, const char* fontPath, FT_Face& face, unsigned int charSize);
    VertexArray mVAO;
    VertexBuffer mVBO;

    std::string mTextToRender;
    std::string mText;

    Shader mShader;

    unsigned int VAO{}, VBO{}, mTextCurrentIterator{};

    std::map<char, Character> mCharacters;
};


#endif //REBIRTH_TEXT_H
