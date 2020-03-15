#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(int argc, const char * argv[]) {

    std::cout << "Hello, my colorful triangle!\n";
    GLFWwindow *window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello OpenGL", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glBegin(GL_TRIANGLES);

        glColor3f(1.0, 0.0, 0.0);    // Red
        glVertex3f(0.0, 1.0, 0.0);

        glColor3f(0.0, 1.0, 0.0);    // Green
        glVertex3f(-1.0, -1.0, 0.0);

        glColor3f(0.0, 0.0, 1.0);    // Blue
        glVertex3f(1.0, -1.0, 0.0);

        glEnd();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}