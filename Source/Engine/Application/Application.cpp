//
// Created by dezlow on 25.09.2021.
//

#include "Application.h"
#include "Engine/Lua/LuaCore.h"
#include "Engine/Core/Core.h"
extern std::vector<VNStatementInfo> StatementsList;
extern const char* vertexShaderSrc;
extern const char* fragmentShaderSrc;
extern std::deque<std::pair<LuaImage*, Shader>> shaders;
extern std::deque<std::pair<LuaImage*, Texture>> textures;

static bool NextState = true;

Application::Application() = default;

Application::~Application() = default;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void Application::Run()
{
    double deltaTime = 0.0f;
    double lastFrame = 0.0f;

    double last = 0.0f, first = 0.0f;
    bool skip = false;

    mTextRender.Init("font.ttf");
    float timerToNextChar = 0.05f;

    float currentAlpha = 0.0f;

    bool DissolveEffect = false;
    bool ReDissolveEffect = false;
    bool ReDissolveEffectSprite = false;

    float currentReAlpha = 1.0f;
    uint32_t tempLastSpriteID = 0;

    while (!glfwWindowShouldClose(mWindowProps.window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        first = glfwGetTime();

        if (DissolveEffect && NextState && currentAlpha < 1.0f && mCurrentIterator > 0)
        {
            currentAlpha = 1.0f;
            NextState = false;
        }
        if (ReDissolveEffect && NextState && currentReAlpha > 0.0f)
        {
            currentReAlpha = 0.0f;
            NextState = false;
        }

        if (!DissolveEffect && !ReDissolveEffect && !ReDissolveEffectSprite)
        {
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
                mBgIDRemove = mCurrentIterator;
                mCurrentIterator++;
                NextState = false;
                goto start;
            case VNStatements::SHOWSPRITE:
                mSprIDsShow.push_back(mCurrentIterator);
                mCurrentIterator++;
                NextState = false;
                goto start;
            case VNStatements::HIDESPRITE:
            {
                mSprIDsRemove.push_back(mCurrentIterator);
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

        if (!textures.empty())
        {
            if (!textures[0].first->IsSprite() && mBgIDRemove > 0)
            {
                if (ReDissolveEffect)
                {
                    currentReAlpha -= 1.5f * (float)deltaTime;
                }
                ReDissolveEffect = true;

                for (uint32_t i = 0; i < shaders.size(); i++)
                {
                    if (shaders[i].first->GetCurrentAlpha() <= 0.0f)
                    {
                        shaders[i].first->UnLoad();
                        ReDissolveEffect = false;
                    }
                    else
                    {
                        shaders[i].second.use();
                        shaders[i].first->SetAlpha(currentReAlpha);
                    }
                }

                if (!ReDissolveEffect)
                {
                    shaders.clear();
                    textures.clear();

                    StatementsList[mBgIDRemove].image->Load();
                    shaders.push_front(std::make_pair(StatementsList[mBgIDRemove].image, StatementsList[mBgIDRemove].image->GetShader()));
                    textures.push_front(std::make_pair(StatementsList[mBgIDRemove].image, StatementsList[mBgIDRemove].image->GetTexture()));
                    mBgIDRemove = 0;
                    currentReAlpha = 1.0f;
                }
            }
            else if (!mSprIDsRemove.empty())
            {
                if (ReDissolveEffectSprite)
                {
                    currentReAlpha -= 2.0f * (float)deltaTime;
                }
                ReDissolveEffectSprite = true;

                uint32_t lastSpriteID = 0;

                for (const auto& SpriteRemoveID : mSprIDsRemove)
                {
                    if (lastSpriteID > 0)
                    {
                        if (StatementsList[lastSpriteID].image->GetCurrentAlpha() > 0.0f)
                        {
                            lastSpriteID = 0;
                            continue;
                        }

                        if (currentReAlpha <= 0.0f)
                        {
                            if (StatementsList[lastSpriteID].image->GetCurrentAlpha() <= 0.0f)
                            {
                                currentReAlpha = 1.0f;
                            }
                        }
                    }

                    if (StatementsList[SpriteRemoveID].image->GetCurrentAlpha() > 0.0f)
                    {
                        StatementsList[SpriteRemoveID].image->GetShader().use();
                        StatementsList[SpriteRemoveID].image->SetAlpha(currentReAlpha);
                    }

                    tempLastSpriteID = lastSpriteID;
                    lastSpriteID = SpriteRemoveID;
                }

                if (StatementsList[mSprIDsRemove[mSprIDsRemove.size() - 1]].image->GetCurrentAlpha() <= 0.1f)
                {
                    ReDissolveEffectSprite = false;
                }

                if (!ReDissolveEffectSprite)
                {
                    for (const auto& SpriteIDRemove : mSprIDsRemove)
                    {
                        const LuaImage* spriteToDelete = std::make_pair(StatementsList[SpriteIDRemove].image, StatementsList[SpriteIDRemove].image->GetShader()).first;
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
                    }
                    mSprIDsRemove.clear();
                    currentReAlpha = 1.0f;
                    tempLastSpriteID = 0;
                    ReDissolveEffectSprite = false;
                }
            }
        }
        else
        {
            StatementsList[mBgIDRemove].image->Load();
            shaders.push_front(std::make_pair(StatementsList[mBgIDRemove].image, StatementsList[mBgIDRemove].image->GetShader()));
            textures.push_front(std::make_pair(StatementsList[mBgIDRemove].image, StatementsList[mBgIDRemove].image->GetTexture()));
            mBgIDRemove = 0;
            if (!mSprIDsShow.empty())
            {
                for (const auto& SpriteIDShow : mSprIDsShow)
                {
                    StatementsList[SpriteIDShow].image->Load();
                    shaders.emplace_back(StatementsList[SpriteIDShow].image, StatementsList[SpriteIDShow].image->GetShader());
                    textures.emplace_back(StatementsList[SpriteIDShow].image, StatementsList[SpriteIDShow].image->GetTexture());
                }
                mSprIDsShow.clear();
            }
        }

        if (!mSprIDsShow.empty() && !ReDissolveEffect)
        {
            for (const auto& SpriteIDShow : mSprIDsShow)
            {
                StatementsList[SpriteIDShow].image->Load();
                shaders.emplace_back(StatementsList[SpriteIDShow].image, StatementsList[SpriteIDShow].image->GetShader());
                textures.emplace_back(StatementsList[SpriteIDShow].image, StatementsList[SpriteIDShow].image->GetTexture());
            }
            mSprIDsShow.clear();
        }

        mVAO.Bind();

        for (int i = 0; i < textures.size() && i < shaders.size(); ++i)
        {
            bool skipDissolve = false;
            if (textures[i].first->GetCurrentAlpha() >= 1.0f)
            {
                skipDissolve = true;
            }

            shaders[i].second.use();

            if (!skipDissolve && !ReDissolveEffect && !ReDissolveEffectSprite)
            {
                if (textures[i].first->GetCurrentAlpha() <= 1.0f)
                {
                    if (i > 0 && textures[i - 1].first->GetCurrentAlpha() >= 1.0f && textures[i].first->IsSprite())
                    {
                        DissolveEffect = true;
                        currentAlpha += 3.0f * (float) deltaTime;
                        textures[i].first->SetAlpha(currentAlpha);

                        if (textures[i].first->GetCurrentAlpha() >= 1.0f)
                        {
                            DissolveEffect = false;
                            currentAlpha = 0.0f;
                            shaders[i].second.SetUniform<glm::mat4>("uMVP", MVP);
                            textures[i].second.Bind();
                            glDrawArrays(GL_TRIANGLES, 0, 6);
                            break;
                        }
                    }
                    else if (!textures[i].first->IsSprite())
                    {
                        DissolveEffect = true;
                        currentAlpha += 0.55f * (float) deltaTime;
                        textures[i].first->SetAlpha(currentAlpha);

                        if (textures[i].first->GetCurrentAlpha() >= 1.0f)
                        {
                            DissolveEffect = false;
                            currentAlpha = 0.0f;
                            shaders[i].second.SetUniform<glm::mat4>("uMVP", MVP);
                            textures[i].second.Bind();
                            glDrawArrays(GL_TRIANGLES, 0, 6);
                            break;
                        }
                    }
                }
            }

            shaders[i].second.SetUniform<glm::mat4>("uMVP", MVP);
            textures[i].second.Bind();
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        if (!DissolveEffect && !ReDissolveEffect && !ReDissolveEffectSprite)
        {
            mVAO.UnBind();
            mTextRender.Render(MVP, 35.0f, 45.0f);
        }

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

    LuaCore::Run(lua);

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