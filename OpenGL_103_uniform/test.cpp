// OPENGL 103 uniform

#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../common/GLShader.h"

struct vec2
{
    float x;
    float y;
};

struct vec3
{
    float x;
    float y;
    float z;
};

using Color = vec3;

struct Vertex
{
    vec2 position;
    Color color;
};

struct Application
{
    GLShader m_basicShader;
    int m_width;
    int m_height;

    // new member variables
    GLuint m_vbo = 0;
    GLuint m_vao = 0;

    inline void setSize(int width, int height) {
        m_width = width;
        m_height = height;
    }

    bool Initialize()
    {
        std::cout << "Carte Graphique : " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "Version OpenGL : " << glGetString(GL_VERSION) << std::endl;
        std::cout << "version GLSL : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

        int numExtensions = 0;
        glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
        for (int i = 0; i < numExtensions; i++) {
            std::cout << "Extensions[" << i << "] " << glGetStringi(GL_EXTENSIONS, i) << std::endl;
        }

        m_basicShader.LoadVertexShader("basic_uniform.vs.glsl");
        m_basicShader.LoadFragmentShader("basic_uniform.fs.glsl");
        m_basicShader.Create();

        // Create VBO and VAO
        glGenBuffers(1, &m_vbo);
        glGenVertexArrays(1, &m_vao);

        // Bind VAO and VBO
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        // Copy the vertices into the VBO
        const Vertex triangle[] = {
            Vertex{vec2{-0.8f, +0.8f}, Color{1.0f, 0.0f, 0.0f}}, // sommet #0
            Vertex{vec2{+0.0f, -0.8f}, Color{0.0f, 1.0f, 0.0f}}, // sommet #1
            Vertex{vec2{+0.8f, +0.8f}, Color{0.0f, 0.0f, 1.0f}} // sommet #2
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

        // Set up the vertex attributes pointers
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

        // Unbind VBO and VAO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        return true;
    }

    void Deinitialize()
    {
        m_basicShader.Destroy();

        // Delete VBO and VAO
        glDeleteBuffers(1, &m_vbo);
        glDeleteVertexArrays(1, &m_vao);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        glBindVertexArray(0);
        glUseProgram(0);
        glDisable(GL_CULL_FACE);

        glfwSwapBuffers(window);
    }
    void Shutdown()
    {
	glfwTerminate();
    }
};

int main() {
    Application app;
    if (!glfwInit()) {
        return 1;
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGL 103 - uniform", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return 1;
    }

    app.setSize(1280, 720);

    if (!app.Initialize()) {
        glfwTerminate();
        return 1;
    }

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        app.Render();
    }

    app.Deinitialize();

    glfwTerminate();

    return 0;
}


