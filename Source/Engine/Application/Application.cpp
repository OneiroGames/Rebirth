//
// Created by dezlow on 25.09.2021.
//

#include "Application.h"
#include "Engine/VNTools/VNScript.h"
#include "Engine/Core/Core.h"
extern std::vector<VNStatementInfo> StatementsList;
extern const char* vertexShaderSrc;
extern const char* fragmentShaderSrc;
extern std::deque<std::pair<const LuaImage*, Shader>> shaders;
extern std::deque<std::pair<const LuaImage*, Texture>> textures;

static bool NextState = true;

Application::Application() = default;

Application::~Application() = default;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        switch (button)
        {
        case GLFW_MOUSE_BUTTON_LEFT:
            NextState = true;
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

    glfwSetMouseButtonCallback(mWindowProps.window, mouse_button_callback);

    stbi_set_flip_vertically_on_load(true);

    lua_close(L);

    L = luaL_newstate();
    luaL_openlibs(L);
    VNScript::Run(L);
    luaL_loadfile(L, mConfigs.GetGameStartFile());
    lua_pcall(L, 0, 0, 0);

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

    lb::LuaRef StartLabel = lb::getGlobal(L, "label_start");
    StartLabel();

    while (!glfwWindowShouldClose(mWindowProps.window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (NextState && mCurrentIterator != StatementsList.size())
        {
            start:
            switch (StatementsList[mCurrentIterator].command)
            {
            case VNStatements::TEXT:
                std::cout << StatementsList[mCurrentIterator].content << std::endl;
                break;
            case VNStatements::SCENE:
                if (textures.empty() && shaders.empty())
                {
                    shaders.push_front(std::make_pair(StatementsList[mCurrentIterator].image, StatementsList[mCurrentIterator].image->GetShader()));
                    textures.push_front(std::make_pair(StatementsList[mCurrentIterator].image, StatementsList[mCurrentIterator].image->GetTexture()));
                }
                else
                {
                    shaders.begin()->operator=(std::make_pair(StatementsList[mCurrentIterator].image, StatementsList[mCurrentIterator].image->GetShader()));
                    textures.begin()->operator=(std::make_pair(StatementsList[mCurrentIterator].image, StatementsList[mCurrentIterator].image->GetTexture()));
                }
                mCurrentIterator++;
                NextState = false;
                goto start;
                break;
            case VNStatements::SHOWSPRITE:
                shaders.push_back(std::make_pair(StatementsList[mCurrentIterator].image, StatementsList[mCurrentIterator].image->GetShader()));
                textures.push_back(std::make_pair(StatementsList[mCurrentIterator].image, StatementsList[mCurrentIterator].image->GetTexture()));
                mCurrentIterator++;
                NextState = false;
                goto start;
            case VNStatements::HIDESPRITE:
            {
                const LuaImage* spriteToDelete = std::make_pair(StatementsList[mCurrentIterator].image, StatementsList[mCurrentIterator].image->GetShader()).first;
                auto shaderIt(shaders.begin());
                auto textureIt(textures.begin());
                for (const auto& shader: shaders)
                {
                    if (shader.first == spriteToDelete)
                    {
                        shaders.erase(shaderIt);
                        textures.erase(textureIt);
                        break;
                    }
                    shaderIt++;
                    textureIt++;
                }
                mCurrentIterator++;
                NextState = false;
                goto start;
            }
            default:
                break;
            }
            mCurrentIterator++;
            NextState = false;
        }

        glfwGetFramebufferSize(mWindowProps.window, &mWindowProps.width, &mWindowProps.height);

        glViewport(0,0, mWindowProps.width, mWindowProps.height);
        glm::mat4 proj = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);;
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));

        glm::mat4 MVP = proj * view;

        mVAO.Bind();

        for (int i = 0; i < textures.size() && i < shaders.size(); ++i)
        {
            shaders[i].second.use();
            shaders[i].second.SetUniform<glm::mat4>("uMVP", MVP);
            shaders[i].second.SetUniform<int>("uTextureWidth", textures[i].second.width);
            shaders[i].second.SetUniform<int>("uTextureHeight", textures[i].second.height);
            textures[i].second.Bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        }

        glfwSwapBuffers(mWindowProps.window);
        glfwPollEvents();
    }
}