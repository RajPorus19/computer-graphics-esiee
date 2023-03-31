#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GLShader.h"

class Application {
public:
    void setSize(int w, int h);
    bool Initialize();
    void Deinitialize();
    void Draw();

private:
    GLFWwindow* window;
    GLuint program;
    GLuint vao;
    GLuint vbo;
};

void Application::setSize(int w, int h) {
    glViewport(0, 0, w, h);
}

bool Application::Initialize() {
    if (!glfwInit()) {
        return false;
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1280, 720, "OpenGL 103 - uniform", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return false;
    }

    GLShader shader;
    shader.LoadFromFile(GL_VERTEX_SHADER, "simple.vs");
    shader.LoadFromFile(GL_FRAGMENT_SHADER, "simple.fs");
    program = shader.CreateAndLinkProgram();

    GLfloat vertices[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.0f, 0.5f
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return true;
}

void Application::Deinitialize() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);

    glfwDestroyWindow(window);

    glfwTerminate();
}

void Application::Draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);
    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
    glUseProgram(0);
}

int main() {
    Application app;

    if (!app.Initialize()) {
        return 1;
    }

    while (!glfwWindowShouldClose(app.window)) {
        glfwPollEvents();

        app.Draw();

        glfwSwapBuffers(app.window);
    }

    app.Deinitialize();

    return 0;
}

