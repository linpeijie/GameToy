#include <iostream>
#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(1000, 1000, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}