#include "input.h"
#include <GLFW/glfw3.h>

extern Window* window_ptr;

void keyboard_callback(GLFWwindow *window, i32 key, i32 scancode, i32 action, i32 modes)
{
    Keyboard *keyboard = window_ptr->keyboard;
    keyboard->keys[key] = action;
}

void mouse_click_callback(GLFWwindow *window, i32 button, i32 action, i32 mods)
{

    Mouse *mouse = window_ptr->mouse;
    mouse->keys[button] = action;
}

void mouse_cursor_callback(GLFWwindow *window, f64 x, f64 y)
{
    Mouse *mouse = window_ptr->mouse;
    mouse->x = x;
    mouse->y = y;
}

void initializeMouse(Mouse *mouse)
{
    for (u32 i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++) {
        mouse->keys[i] = 0;
    }
}

void initializeKeyboard(Keyboard* keyboard) {
    for (u32 i = 0; i < GLFW_KEY_LAST; i++) {
        keyboard->keys[i] = 0;
    }
}

