//
// Created by dezlow on 17.09.2021.
//

#include <iostream>

#ifdef __MINGW64__
    #include "Engine/Core/Platform/Windows/WindowsWindow.h"
#elif __linux__
    #include "Engine/Core/Platform/Linux/LinuxWindow.h"
#endif

#include "Engine/Core/OpenGL/Shader.h"
#include "Engine/Core/OpenGL/VertexArray.h"
#include "Engine/Core/OpenGL/VertexBuffer.h"
#include "Engine/Core/OpenGL/VertexBufferLayout.h"
#include "Engine/Core/OpenGL/IndexBuffer.h"
#include "Engine/Core/OpenGL/Texture.h"

#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"

#include "ImGui/imgui.h"
#include "ImGui/backends/imgui_impl_glfw.h"
#include "ImGui/backends/imgui_impl_opengl3_loader.h"
#include "ImGui/backends/imgui_impl_opengl3.h"

#include "stb/stb_image.h"

int main()
{
    WindowProperties windowProps = WindowHnd::CreateWindow(1280, 720, "Rebirth");

    stbi_set_flip_vertically_on_load(true);

    Texture tex2("../bus_stop.jpg", false);

    const char* vertexShaderSrc = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec2 aTexCoords;
        uniform mat4 uMVP;

        out vec2 TexCoords;

        void main()
        {
            TexCoords = aTexCoords;
            gl_Position = uMVP * vec4(aPos, 1.0);
        }
    )";

    const char* fragmentShaderSrc = R"(
        #version 330 core
        out vec4 FragColor;

        uniform vec3 uColor;
        uniform sampler2D uTexture;

        in vec2 TexCoords;

        void main()
        {
            FragColor = texture(uTexture, TexCoords);
        }
    )";

    Shader sh; sh.LoadFromSource(vertexShaderSrc, fragmentShaderSrc);

    sh.SetUniform("uTexture", 0);

    const float vertices[] = {
            1920.0f,  1080.0f, 0.0f,  1920.0f/tex2.width,  1080.0f/tex2.height,
            1920.0f, -1080.0f, 0.0f,  1920.0f/tex2.width, -1080.0f/tex2.height,
           -1920.0f,  1080.0f, 0.0f, -1920.0f/tex2.width,  1080.0f/tex2.height
    };

    const unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    VertexArray VAO;
    VAO.Bind();
    VertexBuffer VBO(sizeof(vertices), vertices);
    IndexBuffer EBO(sizeof(indices), indices);
    VertexBufferLayout::Push<float>(0,3,5,0);
    VertexBufferLayout::Push<float>(1,2,5,3 * sizeof(float));

    VBO.UnBind();
    VAO.UnBind();

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(windowProps.window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    while (!glfwWindowShouldClose(windowProps.window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /*ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();*/

        glfwGetFramebufferSize(windowProps.window, &windowProps.width, &windowProps.height);
        glViewport(0,0, windowProps.width, windowProps.height);
        glm::mat4 proj = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));

        glm::mat4 MVP = proj * view;

        sh.use();
        sh.SetUniform<glm::mat4>("uMVP", MVP);

        glActiveTexture(GL_TEXTURE0);
        tex2.Bind();
        VAO.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        /*ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());*/

        glfwSwapBuffers(windowProps.window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
