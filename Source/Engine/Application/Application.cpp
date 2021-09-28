//
// Created by dezlow on 25.09.2021.
//

#include "Application.h"

constexpr const char* vertexShaderSrc = R"(
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

constexpr const char* fragmentShaderSrc = R"(
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

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        switch (button)
        {
        case GLFW_MOUSE_BUTTON_LEFT:
            break;
        default:
            break;
        }
    }
}

void Application::Run()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    mConfigs.Run(L);

    luaL_loadfile(L, "config.lua");
    lua_pcall(L, 0, 0, 0);

    mWindowProps = WindowHnd::CreateWindow(mConfigs.GetWindowWidth(), mConfigs.GetWindowHeight(), mConfigs.GetWindowTitle());

    stbi_set_flip_vertically_on_load(true);

    lua_close(L);

    L = luaL_newstate();
    luaL_openlibs(L);
    luaL_loadfile(L, mConfigs.GetGameStartFile());
    lua_pcall(L, 0, 0, 0);

    Shader bgShader;
    bgShader.LoadFromSource(vertexShaderSrc, fragmentShaderSrc);
    mShaders.push_back(bgShader);

    constexpr const float vertices[] = {
            1920.0f,  1080.0f, 0.0f,
            1920.0f, -1080.0f, 0.0f,
           -1920.0f,  1080.0f, 0.0f
    };

    constexpr const unsigned int indices[] = {
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

    mVAO = VAO; mVBO = VBO; mEBO = EBO;

    while (!glfwWindowShouldClose(mWindowProps.window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwGetFramebufferSize(mWindowProps.window, &mWindowProps.width, &mWindowProps.height);

        glViewport(0,0, mWindowProps.width, mWindowProps.height);
        glm::mat4 proj = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);;
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));

        glm::mat4 MVP = proj * view;

        mVAO.Bind();

        for (short int i = 0; i < mTextures.size() && i < mShaders.size(); ++i)
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