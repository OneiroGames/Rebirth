//
// Created by dezlow on 25.09.2021.
//

#include "Application.h"
#include "Engine/VNTools/VNScript.h"
#include "Engine/Core/Core.h"
extern std::vector<VNStatementInfo> StatementsList;
extern const char* vertexShaderSrc;
extern const char* fragmentShaderSrc;
extern std::deque<std::pair<LuaImage*, Shader>> shaders;
extern std::deque<std::pair<LuaImage*, Texture>> textures;

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
    double deltaTime = 0.0f;
    double lastFrame = 0.0f;

    double last = 0.0f, first = 0.0f;
    bool skip = false;

    mTextRender.Init("font.ttf");
    float timerToNextChar = 0.05f;

    while (!glfwWindowShouldClose(mWindowProps.window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        first = glfwGetTime();
        if (timerToNextChar < 0.0f)
        {
            mTextRender.DisplayAllText();
        }
        else
        {
            if (first >= timerToNextChar && !skip)
            {
                last = glfwGetTime();
                skip = true;
            }
            if (skip)
            {
                if (first >= (last + timerToNextChar))
                {
                    last = glfwGetTime();
                    mTextRender.DisplayNextChar();
                }
            }
        }

        if (!mTextRender.isShowAllText() && NextState)
        {
            mTextRender.DisplayAllText();
            NextState = false;
        }

        if (NextState && mCurrentIterator != StatementsList.size())
        {
            start:
            if (mCurrentIterator >= StatementsList.size()) goto end;

            switch (StatementsList[mCurrentIterator].command)
            {
            case VNStatements::TEXT:
                mTextRender.ClearTextToRender();
                mTextRender.SetString(StatementsList[mCurrentIterator].content);
                break;
            case VNStatements::SCENE:
                if (!shaders.empty())
                {
                    for (auto& shader : shaders)
                    {
                        shader.first->UnLoad();
                    }
                }
                shaders.clear();
                textures.clear();

                StatementsList[mCurrentIterator].image->Load();
                shaders.push_front(std::make_pair(StatementsList[mCurrentIterator].image, StatementsList[mCurrentIterator].image->GetShader()));
                textures.push_front(std::make_pair(StatementsList[mCurrentIterator].image, StatementsList[mCurrentIterator].image->GetTexture()));
                mCurrentIterator++;
                NextState = false;
                goto start;
                break;
            case VNStatements::SHOWSPRITE:
                StatementsList[mCurrentIterator].image->Load();
                shaders.emplace_back(StatementsList[mCurrentIterator].image, StatementsList[mCurrentIterator].image->GetShader());
                textures.emplace_back(StatementsList[mCurrentIterator].image, StatementsList[mCurrentIterator].image->GetTexture());
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
                        textureIt->first->UnLoad();
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
            end:
            NextState = false;
        }

        glfwGetFramebufferSize(mWindowProps.window, &mWindowProps.width, &mWindowProps.height);

        glViewport(0,0, mWindowProps.width, mWindowProps.height);
        glm::mat4 proj = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);
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

        mVAO.UnBind();
        mTextRender.Render(MVP, 35.0f, 45.0f);

        glfwSwapBuffers(mWindowProps.window);
        glfwPollEvents();
    }
}

#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"

void Application::Init()
{
    lua.open_libraries(sol::lib::base);
    mConfigs.Run(lua, "config.lua");
    mWindowProps = WindowHnd::CreateWindow(mConfigs.GetWindowWidth(), mConfigs.GetWindowHeight(), mConfigs.GetWindowTitle().c_str());

    glfwSetMouseButtonCallback(mWindowProps.window, mouse_button_callback);
    stbi_set_flip_vertically_on_load(true);

    lua = sol::state();
    lua.open_libraries(sol::lib::base);

    VNScript::Run(lua);
    lua.do_file("script.lua");

    constexpr const float vertices[] = {
            1920.0f,  1080.0f, 0.0f,
            1920.0f, -1080.0f, 0.0f,
           -1920.0f,  1080.0f, 0.0f
    };

    constexpr const unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    mVAO.Init();
    mVAO.Bind();
    mVBO.Create(sizeof(vertices), vertices);
    mEBO.Create(sizeof(indices), indices);
    VertexBufferLayout::Push<float>(0,3,3,0);

    mVAO.UnBind();
    mVBO.UnBind();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);

    sol::protected_function LabelStart = lua["label_start"];

    if (LabelStart.valid())
    {
        LabelStart();
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
