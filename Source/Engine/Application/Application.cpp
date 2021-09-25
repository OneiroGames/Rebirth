//
// Created by dezlow on 25.09.2021.
//

#include "Application.h"

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

        void main()
        {
            vec4 Texture = texture2D(uTexture, vec2(TexCoords.x / uTextureWidth, TexCoords.y / uTextureHeight));
            if(Texture.a < 0.1)
					discard;
            FragColor = Texture;
        }
    )";

Application::Application()
{

}

Application::~Application()
{
}

void Application::Run()
{
    lua_State* L = luaL_newstate();
    luaL_loadfile(L, "script.lua");
    luaL_openlibs(L);
    lua_pcall(L, 0, 0, 0);
    lb::LuaRef LuaWindowProps = lb::getGlobal(L, "window");

    mWindowProps = WindowHnd::CreateWindow(LuaWindowProps["width"].cast<int>(), LuaWindowProps["height"].cast<int>(), LuaWindowProps["title"].cast<const char*>());

    stbi_set_flip_vertically_on_load(true);

    Shader bgShader;
    bgShader.LoadFromSource(vertexShaderSrc, fragmentShaderSrc);
    mShaders.push_back(bgShader);

    const float vertices[] = {
            1920.0f,  1080.0f, 0.0f,
            1920.0f, -1080.0f, 0.0f,
            -1920.0f,  1080.0f, 0.0f
    };

    const unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    VertexArray VAO;
    VAO.Init();
    VAO.Bind();
    VertexBuffer VBO = VertexBuffer(sizeof(vertices), vertices);
    IndexBuffer EBO = IndexBuffer(sizeof(indices), indices);
    VertexBufferLayout::Push<float>(0,3,3,0);

    VAO.UnBind();
    VBO.UnBind();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);

    mStartLabel = lb::getGlobal(L, "label_start");

    mVAO = VAO; mVBO = VBO; mEBO = EBO;

    while (!glfwWindowShouldClose(mWindowProps.window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (mNextState && mLabelTableIt != 0)
        {
            std::cout << mLabelTableIt << std::endl;
            if (mLabelTableIt == mStartLabel.length() + 1)
            {
                mNextState = false;
                mLabelTableIt = 0;
            }
            else
            {
                if (!mStartLabel.rawget(mLabelTableIt)["background"].isNil())
                {
                    if (mTextures.size() == 0)
                    {
                        mTextures.push_back(Texture(mStartLabel.rawget(mLabelTableIt)["background"].cast<std::string>().c_str()));
                    }
                    else
                    {
                        mTextures[0].Load(mStartLabel.rawget(mLabelTableIt)["background"].cast<std::string>().c_str());
                    }
                    mLabelTableIt++;
                }
            }
            mNextState = false;
        }

        glfwGetFramebufferSize(mWindowProps.window, &mWindowProps.width, &mWindowProps.height);

        glViewport(0,0, mWindowProps.width, mWindowProps.height);
        glm::mat4 proj = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);;
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));

        glm::mat4 MVP = proj * view;

        mVAO.Bind();

        for (unsigned int i = 0; i < mTextures.size() && i < mShaders.size(); ++i)
        {
            mShaders[i].use();
            mShaders[i].SetUniform<glm::mat4>("uMVP", MVP);
            mShaders[i].SetUniform<int>("uTextureWidth", mTextures[i].width);
            mShaders[i].SetUniform<int>("uTextureHeight", mTextures[i].height);
            mTextures[i].Bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        }

        glfwSwapBuffers(mWindowProps.window);
        glfwPollEvents();
    }
}
