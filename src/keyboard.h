
#ifdef GLFW_KEY_LAST 
#else 
#define GLFW_KEY_LAST 348
#endif

#include "types.h"

typedef struct Keyboard {

    u8 pressedKeys[GLFW_KEY_LAST + 1];

} Keyboard;

boolean isKeyDown(Keyboard* keyboard, u32 key);
boolean isKeyPressed(Keyboard* keyboard, u32 key);
