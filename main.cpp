#include <GL/glut.h>


void display()
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the four squares
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 1.0f); // Top-left
    glVertex2f(-0.5f, 1.0f); // Top-right
    glVertex2f(-0.5f, 0.5f); // Bottom-right
    glVertex2f(-1.0f, 0.5f); // Bottom-left
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, 1.0f); // Top-left
    glVertex2f(0.0f, 1.0f); // Top-right
    glVertex2f(0.0f, 0.5f); // Bottom-right
    glVertex2f(-0.5f, 0.5f); // Bottom-left
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 1.0f); // Top-left
    glVertex2f(0.5f, 1.0f); // Top-right
    glVertex2f(0.5f, 0.5f); // Bottom-right
    glVertex2f(0.0f, 0.5f); // Bottom-left
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glBegin(GL_QUADS);
    glVertex2f(0.5f, 1.0f); // Top-left
    glVertex2f(1.0f, 1.0f); // Top-right
    glVertex2f(1.0f, 0.5f); // Bottom-right
    glVertex2f(0.5f, 0.5f); // Bottom-left
    glEnd();

    // Swap the buffers
    glutSwapBuffers();
}


int main(int argc, char** argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL - 4 squares");

    // Set up the viewport
    glViewport(0, 0, 800, 600);

    // Set the background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Register the display function
    glutDisplayFunc(display);

    // Enter the main loop
    glutMainLoop();

    return 0;
}
