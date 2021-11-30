//
// Created by dezlow on 01.10.2021.
//

#ifndef REBIRTH_TEXT_H
#define REBIRTH_TEXT_H

#include "OpenGL/ogl4.5.hpp"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <map>
#include <utility>

#include "ft2build.h"
#include FT_FREETYPE_H

struct Character {
    uint32_t TextureID;
    glm::ivec2   Size;
    glm::ivec2   Bearing;
    uint32_t Advance;
};

class Text
{
public:
    Text() = default;

    void Init(const std::string& fontPath, uint16_t charsSize = 32);

    void Render(const glm::mat4& MVP, float x, float y, const glm::vec3& color = glm::vec3(1.0f, 0.4f, 0.1f));
    void SetString(const std::string& text) { mText = text; }
    void DisplayNextChar();
    bool isShowAllText() { return mTextToRender.size() == mText.size(); }
    void DisplayAllText() { mTextToRender = mText; mTextCurrentIterator = mText.size(); }
    void ClearTextToRender() { mTextToRender.clear(); mTextCurrentIterator = 0; }
private:
    void InitFreeType(FT_Library* ft, const char* fontPath, FT_Face& face, unsigned int charSize);

    std::map<char, Character> mCharacters;
    std::string mTextToRender;
    std::string mText;
    VertexArray mVAO;
    VertexBuffer mVBO;
    Shader mShader;
    uint32_t VAO{}, VBO{}, mTextCurrentIterator{};
    uint32_t mCharSize{};


};


#endif //REBIRTH_TEXT_H
