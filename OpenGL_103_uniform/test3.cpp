#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../common/GLShader.h"

class Application {
public:
    bool Initialize();
    void Render();
    void Deinitialize();
    GLFWwindow* GetWindow() const { return window; }
private:
    GLFWwindow* window;
    GLuint program;
};

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
    shader.LoadFromFile("simple.vs", GL_VERTEX_SHADER);
    shader.LoadFromFile("simple.fs", GL_FRAGMENT_SHADER);

    program = shader.CreateAndLinkProgram({});

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    return true;
}

void Application::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);

    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.0f);
    glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();
}

void Application::Deinitialize() {
    glfwSwapBuffers(window);
    glfwTerminate();
}

int main() {
    Application app;
    if (!app.Initialize()) {
        return 1;
    }

    while (!glfwWindowShouldClose(app.GetWindow())) {
        glfwPollEvents();

        app.Render();
    }

    app.Deinitialize();

    return 0;
}

