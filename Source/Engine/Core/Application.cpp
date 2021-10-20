//
// Created by dezlow on 25.09.2021.
//

#include "Application.h"
#include "Engine/Lua/LuaCore.h"
#include "Engine/Core/Core.h"
extern std::vector<VNStatementInfo> StatementsList;
extern std::deque<LuaImage*> images;

/*#include "ImGui/imgui.h"
#include "ImGui/backends/imgui_impl_glfw.h"
#include "ImGui/backends/imgui_impl_opengl3.h"
#include <GL/glu.h>*/

double deltaTime = 0.0f;
static bool NextState = true;
bool VisualNovel = false;
bool LeftButtonPress = false;

Application::Application() = default;

Application::~Application() = default;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void Application::Run()
{
    double lastFrame = 0.0f;

    double last = 0.0f, first = 0.0f;
    bool skip = false;

    mTextRender.Init("font.ttf", 34);
    mTextNameRender.Init("font.ttf", 36);
    float timerToNextChar = 0.03f;

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

        if (!images.empty() && NextState && !images[images.size() - 1]->GetTransition()->isShowed() && !images[0]->GetTransition()->ReSceneEnd())
        {
            NextState = false;
        }

        if (!images.empty() && images[images.size() - 1]->GetTransition()->isShowed() && images[0]->GetTransition()->isShowed())
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

        uint32_t i = 0;
        for (auto& img : images)
        {
            if (!UpdateImage(img, i, MVP))
            {
                continue;
            }
            i++;
        }

        if (!images.empty() && images[images.size() - 1]->GetTransition()->isShowed() && images[0]->GetTransition()->isShowed())
        {
            mTextNameRender.Render(MVP, 185.0f, 270.0f, glm::vec3(1.0f, 0.1f, 0.0f));
            mTextRender.Render(MVP, 190.0f, 230.0f, glm::vec3(0.7f, 1.0f, 0.0f));
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

        glfwSwapBuffers(mWindowProps.window);
    }

    /*ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();*/
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
    lua.require_file("resources", "resources.lua");
    lua.do_file("script.lua");

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
            if (!images.empty())
            {
                images[0]->GetTransition()->SetType(TransitionTypes::REDISSOLVE);
                NewBGId = mCurrentIterator;
            }
            else
            {
                images.push_front(StatementsList[mCurrentIterator].image);
            }
            mCurrentIterator++;
            NextState = false;
            goto start;
        case VNStatements::SHOWSPRITE:
            images.push_back(StatementsList[mCurrentIterator].image);
            StatementsList[mCurrentIterator].image->GetTransition()->SetType(TransitionTypes::DISSOLVE);
            mCurrentIterator++;
            NextState = false;
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

bool Application::UpdateImage(LuaImage* img, uint32_t& it, glm::mat4& MVP)
{
    if (img->isLoaded())
    {
        img->GetShader()->use();
        img->GetShader()->SetUniform<glm::mat4>("uMVP", MVP);
        img->GetTexture()->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    img->GetTransition()->UpdateReSprite(deltaTime);
    img->GetTransition()->UpdateReScene(deltaTime);

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
        }
    }
    else
    {
        img->GetTransition()->UpdateScene(deltaTime);
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
            if (LeftButtonPress)
            {
                LeftButtonPress = false;
            }
            else
            {
                LeftButtonPress = true;
            }
            break;
        default:
            break;
        }
    }
}