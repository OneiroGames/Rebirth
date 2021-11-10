//
// Created by dezlow on 25.09.2021.
//

#include "Application.h"
#include "Editor/Lua/LuaCore.h"
#include "Runtime/Core/Core.h"

extern std::vector<VNStatementInfo> StatementsList;
extern std::deque<LuaSprite*> sprites;
extern LuaScene* scene;

/*#include "ImGui/imgui.h"
#include "ImGui/backends/imgui_impl_glfw.h"
#include "ImGui/backends/imgui_impl_opengl3.h"
#include <GL/glu.h>*/

double deltaTime = 0.0f;
static bool NextState = true;
bool LeftButtonPress = false;
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
    float timerToNextChar = 0.02f;

    /*bool st = true;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(mWindowProps.window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    bool ts = true;*/

    while (!glfwWindowShouldClose(mWindowProps.window))
    {
        glfwPollEvents();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /*double CursorPosX{}, CursorPosY{};

        glfwGetCursorPos(mWindowProps.window, &CursorPosX, &CursorPosY);

        GLdouble modelView[16];
        GLdouble projection[16];
        GLint viewport[4];
        glGetDoublev(GL_MODELVIEW_MATRIX,modelView);
        glGetDoublev(GL_PROJECTION_MATRIX,projection);
        glGetIntegerv(GL_VIEWPORT,viewport);

        double tx, ty, tz;
        gluUnProject(CursorPosX, CursorPosY,0.0, modelView,projection, viewport, &tx, &ty, &tz);
git clone --recurse-submodules $(sed -n "$i, 1p" modules.txt)
        if (tx >= 0.45 && tx <= 1.0 && ty >= 0.2 && ty <= 1.0)
        {
            ts = true;
        }
        else
        {
            ts = false;
        }*/

        glfwGetFramebufferSize(mWindowProps.window, &mWindowProps.width, &mWindowProps.height);
        glViewport(0, 0, mWindowProps.width, mWindowProps.height);

        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        first = glfwGetTime();
        mTextNameRender.DisplayAllText();

        glm::mat4 proj = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));

        glm::mat4 MVP = proj * view;

        mVAO.Bind();

        if (scene && NextState && !sprites[sprites.size() - 1]->GetTransition()->isShowed() && !scene->GetTransition()->ReSceneEnd())
        {
            NextState = false;
        }

        if (NextState && mTextBox.ReDissolveEnabled() || mTextBox.DissolveEnabled())
        {
            if (scene && sprites[sprites.size() - 1]->GetTransition()->isShowed())
            {
                NextState = false;
            }
        }

        if (!sprites.empty() && sprites[sprites.size() - 1]->GetTransition()->isShowed() && scene->GetTransition()->isShowed() && !mTextBox.ReDissolveEnabled() && !mTextBox.DissolveEnabled())
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

        NextStatement();

        if (scene->isLoaded())
        {
            scene->GetShader()->use();
            scene->GetShader()->SetUniform<glm::mat4>("uMVP", MVP);
            scene->GetTexture()->Bind();
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        uint32_t i = 0;
        for (auto& img : sprites)
        {
            if (!UpdateImage(std::make_pair(scene, img), i, MVP))
            {
                continue;
            }
            i++;
        }

        scene->GetTransition()->UpdateScene(deltaTime);

        if (mTextBox.ReDissolveEnabled())
        {
            mTextBox.GetSprite()->GetShader()->use();
            mTextBox.GetSprite()->GetShader()->SetUniform<glm::mat4>("uMVP", MVP);
            mTextBox.GetSprite()->GetTexture()->Bind();

            glDrawArrays(GL_TRIANGLES, 0, 6);

            mTextBox.Update(deltaTime);
        }

        if (!sprites.empty() && sprites[sprites.size() - 1]->GetTransition()->isShowed() && scene->GetTransition()->isShowed())
        {
            if (!mTextBox.ReDissolveEnabled())
            {
                mTextBox.GetSprite()->GetShader()->use();
                mTextBox.GetSprite()->GetShader()->SetUniform<glm::mat4>("uMVP", MVP);
                mTextBox.GetSprite()->GetTexture()->Bind();

                glDrawArrays(GL_TRIANGLES, 0, 6);

                mTextBox.Update(deltaTime);
            }

            if (!mTextBox.ReDissolveEnabled() && !mTextBox.DissolveEnabled())
            {
                mTextNameRender.Render(MVP, 185.0f, 270.0f, glm::vec3(1.0f, 0.1f, 0.0f));
                mTextRender.Render(MVP, 190.0f, 230.0f, glm::vec3(0.7f, 1.0f, 0.0f));
            }
        }

        /*ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Debug");
        ImGui::Text("Mouse X: %f", (float)tx);
        ImGui::Text("Mouse Y: %f", (float)ty);
        ImGui::Text("Mouse Button Hover: %i", ts);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());*/

        isStartGame = false;

        glfwSwapBuffers(mWindowProps.window);
    }

    /*ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();*/
}

void Application::Init()
{
    lua.open_libraries(sol::lib::base);
    mConfigs.Run(lua, "game/data/scripts/config.lua");
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
    VertexBufferLayout::Push<float>(0,3,3,0);

    VertexArray::UnBind();
    VertexBuffer::UnBind();


    sol::protected_function LabelStart = lua["label_start"];

    if (LabelStart.valid())
    {
        LabelStart();
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
            if (scene)
            {
                scene->GetTransition()->SetType(TransitionTypes::REDISSOLVE);
                NewBGId = mCurrentIterator;
            }
            else
            {
                scene = StatementsList[mCurrentIterator].scene;
            }

            if (!isStartGame)
            {
                if (mTextBox.isShowed())
                {
                    mTextBox.SetReDissolveEnabled();
                }
            }

            mCurrentIterator++;
            NextState = false;
            goto start;
        }
        case VNStatements::SHOWSPRITE:
            sprites.push_back(StatementsList[mCurrentIterator].sprite);
            StatementsList[mCurrentIterator].sprite->GetTransition()->SetType(TransitionTypes::DISSOLVE);
            mCurrentIterator++;
            NextState = false;
            if (mTextBox.isShowed() && !isStartGame)
            {
                mTextBox.SetReDissolveEnabled();
            }
            goto start;
        case VNStatements::HIDESPRITE:
        {
            for (auto& img : sprites)
            {
                if (img == StatementsList[mCurrentIterator].sprite)
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

bool Application::UpdateImage(std::pair<LuaScene*, LuaSprite*> imgs, uint32_t& it, glm::mat4& MVP)
{
    /*if (imgs.first && imgs.first->isLoaded())
    {
        imgs.first->GetShader()->use();
        imgs.first->GetShader()->SetUniform<glm::mat4>("uMVP", MVP);
        imgs.first->GetTexture()->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }*/

    if (imgs.second && imgs.second->isLoaded())
    {
        imgs.second->GetShader()->use();
        imgs.second->GetShader()->SetUniform<glm::mat4>("uMVP", MVP);
        imgs.second->GetTexture()->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    if (mTextBox.ReDissolveEnabled())
    {
        return true;
    }
    else
    {
        imgs.second->GetTransition()->UpdateReSprite(deltaTime);
        scene->GetTransition()->UpdateReScene(deltaTime);

        if (scene->GetTransition()->ReSceneEnd() && NewBGId > 0)
        {
            StatementsList[NewBGId].scene->GetTransition()->SetType(TransitionTypes::DISSOLVE);
            scene->Destroy();
            scene = StatementsList[NewBGId].scene;
            NewBGId = 0;
        }

        if (scene->GetTransition()->isShowed())
        {
            if (!sprites[it]->GetTransition()->isShowed())
            {
                sprites[it]->GetTransition()->UpdateSprite(deltaTime);
                return false;
            }
            else
            {
                sprites[it]->GetTransition()->UpdateSprite(deltaTime);
            }
        }
    }

    return true;
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