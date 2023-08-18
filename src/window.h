#pragma once

#define LAST_MOUSE_KEY  7
#define LAST_KEYBOARD_KEY 348

#define RELEASE 0 
#define PRESS 1
#define HOLD 2

#include "types.h"

typedef struct Mouse {
    f64 x, y;
    u8 keys[LAST_MOUSE_KEY];
} Mouse;

typedef struct Keyboard {
     u8 keys[LAST_KEYBOARD_KEY];
} Keyboard;

typedef struct Window {
    u16 width;
    u16 height;
    boolean resizable;
    Keyboard* keyboard;
    Mouse* mouse;
    
} Window;

inline boolean isKeyDown(Window* window, u32 key) { return window->keyboard->keys[key] > RELEASE; }
inline boolean isKeyPressed(Window* window, u32 key) { return isKeyPressed(window, key); };

inline boolean isMouseButtonPressed(Window* window, u8 key) { 
    return window->mouse->keys[key] == PRESS;
}