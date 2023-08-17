#include <GLFW/glfw3.h>
#include <stdio.h>
#include "window.h"
#include "keyboard.h"

int main(void)
{
    GLFWwindow* window;

    if(!glfwInit()) {
        return 1;
    }

    Window s_Window = { 800, 600, FALSE };
    Keyboard keyboard;

    glfwWindowHint(GLFW_RESIZABLE, s_Window.resizable);

    window = glfwCreateWindow(s_Window.width, s_Window.height, "Application", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    } 
    
    glfwMakeContextCurrent(window);

    /*Loop until the user closes the window*/
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
