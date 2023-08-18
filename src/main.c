#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#include "input.h"

void err_callback(i32 code, const char *msg);

Window *window_ptr;

int main(void)
{
    GLFWwindow *g_Window;

    if (!glfwInit())
    {
        return 1;
    }

    Window s_Window = {800, 600, FALSE};
    window_ptr = &s_Window;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, s_Window.resizable);

    g_Window = glfwCreateWindow(s_Window.width, s_Window.height, "Application", NULL, NULL);

    if (!g_Window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(g_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    glViewport(0, 0, s_Window.width, s_Window.height);

    // Initialize keyboard
    Keyboard keyboard;
    s_Window.keyboard = &keyboard;
    initializeKeyboard(&keyboard);

    Mouse mouse;
    s_Window.mouse = &mouse;
    initializeMouse(&mouse);

    glfwSetErrorCallback(err_callback);
    glfwSetKeyCallback(g_Window, keyboard_callback);
    glfwSetCursorPosCallback(g_Window, mouse_cursor_callback);
    glfwSetMouseButtonCallback(g_Window, mouse_click_callback);

    f32 vertices[] = {
        0.0f, 0.5f, 0,
        0.5f, -0.5f, 0,
        -0.5f, -0.5f, 0
    };

    u32 vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);

    glBindVertexArray(vertexArrayObject);

    u32 vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";

    u32 vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    i32 shaderCreationResult;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shaderCreationResult);

    if (!shaderCreationResult)
    {
        char shaderCreationLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, shaderCreationLog);
        printf("Error compiling shader: %s\n", shaderCreationLog);
        return -1;
    }

    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 color;\n"
                                       ""
                                       "void main() {"
                                       "   color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}";

    u32 fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &shaderCreationResult);

    if (!shaderCreationResult)
    {
        char shaderCreationLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, shaderCreationLog);
        printf("Error compiling fragment shader: %s\n", shaderCreationLog);
        return -1;
    }

    u32 shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    u32 amountOfObjects = 3;
    u32 stride = sizeof(f32) * amountOfObjects;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
    glEnableVertexAttribArray(0);

    /*Loop until the user closes the window*/
    while (!glfwWindowShouldClose(g_Window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(g_Window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void err_callback(i32 code, const char *msg)
{
    printf("Error while running the program, code %d, information: %s\n", code, msg);
}