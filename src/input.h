#include <GLFW/glfw3.h>
#include "window.h"

void keyboard_callback(GLFWwindow *window, i32 key, i32 scancode, i32 action, i32 modes);
void mouse_cursor_callback(GLFWwindow *window, f64 x, f64 y);
void mouse_click_callback(GLFWwindow *window, i32 button, i32 action, i32 mods);
void initializeKeyboard(Keyboard *keyboard);
void initializeMouse(Mouse *mouse);