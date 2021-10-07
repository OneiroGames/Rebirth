//
// Created by dezlow on 01.10.2021.
//

#include "Text.h"

void Text::Init(const char* fontPath, unsigned int charsSize)
{
    mCharSize = charsSize;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    const char* vertexShaderSrc = R"(
			#version 330 core
			layout(location = 0) in vec4 vertex;
			out vec2 TexCoords;
			uniform mat4 MVP;
			void main()
			{
				gl_Position = MVP * vec4(vertex.xy, 0.0, 1.0);
				TexCoords = vertex.zw;
			}
		)";

    const char* fragmentShaderSrc = R"(
			#version 330 core
			in vec2 TexCoords;
			out vec4 color;
			uniform sampler2D text;
			uniform vec3 textColor;
			void main()
			{
				vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
				color = vec4(textColor, 1.0) * sampled;
			}
		)";

    mShader.LoadFromSource(vertexShaderSrc, fragmentShaderSrc);

    FT_Library ft;

    if (FT_Init_FreeType(&ft))
        throw std::runtime_error("Failed to init freetype!");

    FT_Face face;

    if (FT_New_Face(ft, fontPath, 0, &face))
    {
    }
    else {
        FT_Set_Pixel_Sizes(face, 0, charsSize);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for (unsigned int c = 0; c < 256; c++)
        {
            if ((c >= 0xC0) && (c <= 0xDF))
            {
                if (FT_Load_Char(face, 0x0410 + (c - 0xC0), FT_LOAD_RENDER))
                {
                    std::cout << "FreeType: failed to load glyph!" << std::endl;
                    continue;
                }
            }
            else if ((c >= 0xE0) && (c <= 0xFF))
            {
                if (FT_Load_Char(face, 0x0430 + (c - 0xE0), FT_LOAD_RENDER))
                {
                    std::cout << "FreeType: failed to load glyph!" << std::endl;
                    continue;
                }
            }
            else if (c == 0xA8)
            {
                if (FT_Load_Char(face, 0x0401, FT_LOAD_RENDER))
                {
                    std::cout << "FreeType: failed to load glyph!" << std::endl;
                    continue;
                }
            }
            else if (c == 0xB8)
            {
                if (FT_Load_Char(face, 0x0451, FT_LOAD_RENDER))
                {
                    std::cout << "FreeType: failed to load glyph!" << std::endl;
                    continue;
                }
            }
            else if (c == 0x85)
            {
                if (FT_Load_Char(face, 0x2026, FT_LOAD_RENDER))
                {
                    std::cout << "FreeType: failed to load glyph!" << std::endl;
                    continue;
                }
            }
            else
            {
                if (FT_Load_Char(face, c, FT_LOAD_RENDER))
                {
                    std::cout << "FreeType: failed to load glyph!" << std::endl;
                    continue;
                }
            }

            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer
            );

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            Character character = {
                    texture,
                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    static_cast<unsigned int>(face->glyph->advance.x)
            };
            mCharacters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void Text::Render(const glm::mat4 MVP, float x, float y)
{
    mShader.use();
    mShader.SetUniform<glm::mat4>("MVP", MVP);
    mShader.SetUniform<glm::vec3>("textColor", glm::vec3(1.0f, 0.4f, 0.1f));

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    std::string::iterator c;
    float xpos = 0.0f, ypos = 0.0f;
    float tempx = x;
    Character ch{};
    for (c = mTextToRender.begin(); c != mTextToRender.end(); c++)
    {
        if (*c == '\n')
        {
            x = tempx;
            y -= mCharSize * 1.1;
            continue;
        }

        ch = mCharacters[*c];

        xpos = x + ch.Bearing.x * 1.0f;
        ypos = y - (ch.Size.y - ch.Bearing.y) * 1.0f;

        float w = ch.Size.x * 1.0f;
        float h = ch.Size.y * 1.0f;

        float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        glBindTexture(GL_TEXTURE_2D, ch.TextureID);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.Advance >> 6) * 1.0f - 2;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::DisplayNextChar()
{
    if (mTextCurrentIterator < mText.size())
    {
        mTextToRender.push_back(mText[mTextCurrentIterator]);
        mTextCurrentIterator++;
    }
    else
    {
        return;
    }
}

void Text::InitFreeType(FT_Library* ft, const char* fontPath, FT_Face& face, unsigned int charSize)
{
    if (FT_New_Face(*ft, fontPath, 0, &face)) {
        std::runtime_error("FreeType: failed to load font in " + std::string(fontPath) + " path!");
    }
    else {
        FT_Set_Pixel_Sizes(face, 0, charSize);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for (unsigned int c = 0; c < 256; c++)
        {
            if ((c >= 0xC0) && (c <= 0xDF))
            {
                if (FT_Load_Char(face, 0x0410 + (c - 0xC0), FT_LOAD_RENDER))
                {

                    continue;
                }
            }
            else if ((c >= 0xE0) && (c <= 0xFF))
            {
                if (FT_Load_Char(face, 0x0430 + (c - 0xE0), FT_LOAD_RENDER))
                {
                    continue;
                }
            }
            else if (c == 0xA8)
            {
                if (FT_Load_Char(face, 0x0401, FT_LOAD_RENDER))
                {
                    continue;
                }
            }
            else if (c == 0xB8)
            {
                if (FT_Load_Char(face, 0x0451, FT_LOAD_RENDER))
                {
                    continue;
                }
            }
            else if (c == 0x85)
            {
                if (FT_Load_Char(face, 0x2026, FT_LOAD_RENDER))
                {
                    continue;
                }
            }
            else
            {
                if (FT_Load_Char(face, c, FT_LOAD_RENDER))
                {
                    continue;
                }
            }

            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer
            );

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            Character character = {
                    texture,
                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    static_cast<unsigned int>(face->glyph->advance.x)
            };
            mCharacters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    FT_Done_Face(face);
}
