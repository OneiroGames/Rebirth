//
// Created by dezlow on 01.10.2021.
//

#include "Text.h"

void Text::Init(const std::string& fontPath, uint16_t charsSize)
{
    mCharSize = charsSize;

    gl::GenVertexArrays(1, &VAO);
    gl::GenBuffers(1, &VBO);
    gl::BindVertexArray(VAO);
    gl::BindBuffer(gl::ARRAY_BUFFER, VBO);
    gl::BufferData(gl::ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, gl::DYNAMIC_DRAW);
    gl::EnableVertexAttribArray(0);
    gl::VertexAttribPointer(0, 4, gl::FLOAT, gl::FALSE_, 4 * sizeof(float), nullptr);
    gl::BindBuffer(gl::ARRAY_BUFFER, 0);
    gl::BindVertexArray(0);

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

    if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
    {
    }
    else {
        FT_Set_Pixel_Sizes(face, 0, charsSize);

        gl::PixelStorei(gl::UNPACK_ALIGNMENT, 1);

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
            gl::GenTextures(1, &texture);
            gl::BindTexture(gl::TEXTURE_2D, texture);
            gl::TexImage2D(
                    gl::TEXTURE_2D,
                    0,
                    gl::RED,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0,
                    gl::RED,
                    gl::UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer
            );

            gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::CLAMP_TO_EDGE);
            gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::CLAMP_TO_EDGE);
            gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR_MIPMAP_LINEAR);
            gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR_MIPMAP_LINEAR);
            gl::GenerateMipmap(gl::TEXTURE_2D);

            Character character = {
                    texture,
                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    static_cast<unsigned int>(face->glyph->advance.x)
            };
            mCharacters.insert(std::pair<char, Character>(c, character));
        }
        gl::BindTexture(gl::TEXTURE_2D, 0);
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void Text::Render(const glm::mat4& MVP, float x, float y, const glm::vec3& color)
{
    mShader.use();
    mShader.SetUniform<glm::mat4>("MVP", MVP);
    mShader.SetUniform<glm::vec3>("textColor", color);

    gl::ActiveTexture(gl::TEXTURE0);
    gl::BindVertexArray(VAO);

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

        gl::BindTexture(gl::TEXTURE_2D, ch.TextureID);

        gl::BindBuffer(gl::ARRAY_BUFFER, VBO);
        gl::BufferSubData(gl::ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        gl::BindBuffer(gl::ARRAY_BUFFER, 0);

        gl::DrawArrays(gl::TRIANGLES, 0, 6);

        x += (ch.Advance >> 6) * 1.0f - 2;
    }
    gl::BindVertexArray(0);
    gl::BindTexture(gl::TEXTURE_2D, 0);
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

        gl::PixelStorei(gl::UNPACK_ALIGNMENT, 1);

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
            gl::GenTextures(1, &texture);
            gl::BindTexture(gl::TEXTURE_2D, texture);
            gl::TexImage2D(
                    gl::TEXTURE_2D,
                    0,
                    gl::RED,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0,
                    gl::RED,
                    gl::UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer
            );

            gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::CLAMP_TO_EDGE);
            gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::CLAMP_TO_EDGE);
            gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
            gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);

            Character character = {
                    texture,
                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    static_cast<unsigned int>(face->glyph->advance.x)
            };
            mCharacters.insert(std::pair<char, Character>(c, character));
        }
        gl::BindTexture(gl::TEXTURE_2D, 0);
    }

    FT_Done_Face(face);
}
