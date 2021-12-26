//
// Created by Dezlow on 25.09.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#include "Application.h"
#include "Editor/Lua/LuaCore.h"
#include "Runtime/Core/Core.h"
extern std::vector<VNStatementInfo> StatementsList;
extern std::deque<LuaImage*> images;

double deltaTime = 0.0f;
bool NextState = true;
bool isStartGame = true;

Application::Application() = default;

Application::~Application() = default;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void Application::Run()
{
    double lastFrame = 0.0f;
    double last = 0.0f, first = 0.0f;
    bool skip = false;
    mTextRender.Init("game/data/fonts/font.ttf", 34);
    mTextNameRender.Init("game/data/fonts/font.ttf", 36);
    float timerToNextChar = 0.05f;

    glm::mat4 proj = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));

    glm::mat4 MVP = proj * view;

    while (!glfwWindowShouldClose(mWindowProps.window))
    {
        glfwPollEvents();

        gl::ClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

        glfwGetFramebufferSize(mWindowProps.window, &mWindowProps.width, &mWindowProps.height);
        gl::Viewport(0, 0, mWindowProps.width, mWindowProps.height);

        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        first = glfwGetTime();

        mTextNameRender.DisplayAllText();

        mVAO.Bind();

        if (!images.empty() && NextState && !images[images.size() - 1]->GetTransition()->isShowed() && !images[0]->GetTransition()->ReSceneEnd())
        {
            NextState = false;
        }

        if (NextState && mTextBox.ReDissolveEnabled() || mTextBox.DissolveEnabled() && !images.empty() && images[images.size() - 1]->GetTransition()->isShowed())
        {
            NextState = false;
        }

        if (!images.empty() && images[images.size() - 1]->GetTransition()->isShowed() && images[0]->GetTransition()->isShowed() && !mTextBox.ReDissolveEnabled() && !mTextBox.DissolveEnabled())
        {
            if (timerToNextChar < 0.0f)
            {
                mTextRender.DisplayAllText();
            }
            else
            {
                if (first + timerToNextChar >= timerToNextChar && !skip)
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

        NextStatement();

        uint32_t i = 0;
        for (auto& img : images)
        {
            if (!UpdateImage(img, i, MVP))
            {
                continue;
            }
            i++;
        }

        if (mTextBox.ReDissolveEnabled())
        {
            mTextBox.GetImage()->GetShader()->use();
            mTextBox.GetImage()->GetShader()->SetUniform("uMVP", MVP);
            mTextBox.GetImage()->GetTexture()->Bind();

            gl::DrawArrays(gl::TRIANGLES, 0, 6);

            mTextBox.Update(deltaTime);
        }

        if (!images.empty() && images[images.size() - 1]->GetTransition()->isShowed() && images[0]->GetTransition()->isShowed())
        {
            if (!mTextBox.ReDissolveEnabled())
            {
                mTextBox.GetImage()->GetShader()->use();
                mTextBox.GetImage()->GetShader()->SetUniform("uMVP", MVP);
                mTextBox.GetImage()->GetTexture()->Bind();

                gl::DrawArrays(gl::TRIANGLES, 0, 6);

                mTextBox.Update(deltaTime);
            }

            if (!mTextBox.ReDissolveEnabled() && !mTextBox.DissolveEnabled())
            {
                mTextNameRender.Render(MVP, 185.0f, 270.0f, glm::vec3(1.0f, 0.1f, 0.0f));
                mTextRender.Render(MVP, 190.0f, 230.0f, glm::vec3(0.7f, 1.0f, 0.0f));
            }
        }

        isStartGame = false;

        glfwSwapBuffers(mWindowProps.window);
    }
}

void Application::Init()
{
    lua.open_libraries(sol::lib::base);
    mConfigs.Run(lua, "config.lua");
    mWindowProps = WindowHnd::CreateWindow(mConfigs.GetWindowWidth(), mConfigs.GetWindowHeight(), mConfigs.GetWindowTitle().c_str());

    glfwSetMouseButtonCallback(mWindowProps.window, mouse_button_callback);
    stbi_set_flip_vertically_on_load(true);

    lua = sol::state();
    lua.open_libraries(sol::lib::base, sol::lib::package);
    LuaCore::Run(lua);
    lua.require_file("resources", "game/data/scripts/resources.lua");

    lua.do_file("game/data/scripts/script.lua");

    mTextBox.Init("game/data/ui/textbox.png");

    constexpr const float vertices[] = {
            1920.0f,  1080.0f, 0.0f,
            1920.0f, -1080.0f, 0.0f,
           -1920.0f,  1080.0f, 0.0f
    };

    mVAO.Init();
    mVAO.Bind();
    mVBO.Create(sizeof(vertices), vertices);
    mVBO.PushLayout<float>(0, 3, 3, 0);
    mVAO.UnBind();
    mVBO.UnBind();

    sol::protected_function LabelStart = lua["label_start"];

    if (LabelStart.valid())
    {
        LabelStart();
    }

    gl::Enable(gl::DEPTH_TEST);
    gl::DepthFunc(gl::ALWAYS);
    gl::Enable(gl::BLEND);
    gl::BlendFunc(gl::SRC_ALPHA, gl::ONE_MINUS_SRC_ALPHA);
}

void Application::NextStatement()
{
    if (NextState && mCurrentIterator != StatementsList.size())
    {
        start:
        if (mCurrentIterator >= StatementsList.size()) goto end;

        switch (StatementsList[mCurrentIterator].command)
        {
        case VNStatements::TEXT:
        {
            mTextRender.ClearTextToRender();
            std::string st = StatementsList[mCurrentIterator].content;
            st.erase(st.find(": "));
            StatementsList[mCurrentIterator].content.erase(0, StatementsList[mCurrentIterator].content.find(": ") + 2);
            mTextNameRender.SetString(st);
            mTextRender.SetString(StatementsList[mCurrentIterator].content);
            break;
        }
        case VNStatements::SCENE:
        {
            if (!images.empty())
            {
                images[0]->GetTransition()->SetType(TransitionTypes::REDISSOLVE);
                NewBGId = mCurrentIterator;
            }
            else
            {
                images.push_front(StatementsList[mCurrentIterator].image);
            }

            if (!isStartGame && mTextBox.isShowed())
                mTextBox.SetReDissolveEnabled();

            mCurrentIterator++;
            NextState = false;
            goto start;
        }
        case VNStatements::SHOWSPRITE:
            images.push_back(StatementsList[mCurrentIterator].image);
            StatementsList[mCurrentIterator].image->GetTransition()->SetType(TransitionTypes::DISSOLVE);
            mCurrentIterator++;
            NextState = false;
            if (mTextBox.isShowed() && !isStartGame)
            {
                mTextBox.SetReDissolveEnabled();
            }
            goto start;
        case VNStatements::HIDESPRITE:
        {
            for (auto& img : images)
            {
                if (img == StatementsList[mCurrentIterator].image)
                {
                    img->GetTransition()->SetType(TransitionTypes::REDISSOLVE);
                }
            }
            mCurrentIterator++;
            NextState = false;
            if (mTextBox.isShowed())
            {
                mTextBox.SetReDissolveEnabled();
            }
            goto start;
        }
        default:
            break;
        }
        mCurrentIterator++;
        end:
        NextState = false;
    }
}

bool Application::UpdateImage(LuaImage* img, uint32_t it, glm::mat4& MVP)
{
    if (img->isLoaded())
    {
        img->GetShader()->use();
        img->GetShader()->SetUniform("uMVP", MVP);
        img->GetTexture()->Bind();
        gl::DrawArrays(gl::TRIANGLES, 0, 6);
    }

    if (mTextBox.ReDissolveEnabled())
    {
        return true;
    }
    else
    {
        img->GetTransition()->UpdateReSprite(deltaTime);
        img->GetTransition()->UpdateReScene(deltaTime);

        if (it == images.size())
            return true;

        if (img->GetTransition()->ReSceneEnd() && NewBGId > 0)
        {
            images.push_front(StatementsList[NewBGId].image);
            images.begin().operator*()->GetTransition()->SetType(TransitionTypes::DISSOLVE);
            NewBGId = 0;
        }

        if (images[0]->GetTransition()->isShowed())
        {
            if (!images[it]->GetTransition()->isShowed())
            {
                images[it]->GetTransition()->UpdateSprite(deltaTime);
                return false;
            }
            else
            {
                images[it]->GetTransition()->UpdateSprite(deltaTime);
                return true;
            }
        }
        else
        {
            img->GetTransition()->UpdateScene(deltaTime);
        }
    }

    return true;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        NextState = true;
    }
}