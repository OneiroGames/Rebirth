//
// Created by dezlow on 29.09.2021.
//

#include "Core.h"

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
            FragColor = vec4(Texture.rgb, uTextureAlpha);
        }
    )";

std::vector<VNStatementInfo> StatementsList;
std::deque<std::pair<LuaImage*, Shader>> shaders;
std::deque<std::pair<LuaImage*, Texture>> textures;