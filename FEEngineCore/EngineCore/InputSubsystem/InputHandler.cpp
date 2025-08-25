#include "InputHandler.h"

#include "SDL3/SDL.h"

FE::InputHandler::InputHandler() {

}

void FE::InputHandler::PollEvents(float deltaTime)
{
    SDL_Event SDLevent;

    while (SDL_PollEvent(&SDLevent)) 
    {

        InputEvent event{};
        switch (SDLevent.type) {

        case SDL_EVENT_QUIT:
            event.type = FE_EVENT_QUIT;
            event.timestamp = SDLevent.common.timestamp;
            break;

        case SDL_EVENT_KEY_DOWN:
            event.type = FE_EVENT_KEY_DOWN;
            event.timestamp = SDLevent.key.timestamp;
            event.key.keycode = SDLevent.key.key;
            event.key.scancode = static_cast<FE_Scancode>(SDLevent.key.scancode);
            break;

        case SDL_EVENT_KEY_UP:
            event.type = FE_EVENT_KEY_UP;
            event.timestamp = SDLevent.key.timestamp;
            event.key.keycode = SDLevent.key.key;
            event.key.scancode = static_cast<FE_Scancode>(SDLevent.key.scancode);
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            event.type = FE_EVENT_MOUSE_BUTTON_DOWN;
            event.timestamp = SDLevent.button.timestamp;
            event.mouseBtn.button = SDLevent.button.button;
            event.mouseBtn.clicks = SDLevent.button.clicks;
            event.mouseBtn.down = SDLevent.button.down;
            event.mouseBtn.x = SDLevent.button.x;
            event.mouseBtn.y = SDLevent.button.y;
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            event.type = FE_EVENT_MOUSE_BUTTON_UP;
            event.timestamp = SDLevent.button.timestamp;
            event.mouseBtn.button = SDLevent.button.button;
            event.mouseBtn.clicks = SDLevent.button.clicks;
            event.mouseBtn.down = SDLevent.button.down;
            event.mouseBtn.x = SDLevent.button.x;
            event.mouseBtn.y = SDLevent.button.y;
            break;

        case SDL_EVENT_MOUSE_MOTION:
            event.type = FE_EVENT_MOUSE_MOTION;
            event.timestamp = SDLevent.motion.timestamp;
            event.mouseMotion.x = SDLevent.motion.x;
            event.mouseMotion.y = SDLevent.motion.y;
            event.mouseMotion.xRel = SDLevent.motion.xrel;
            event.mouseMotion.yRel = SDLevent.motion.yrel;
            break;

        case SDL_EVENT_MOUSE_WHEEL:
            event.type = FE_EVENT_MOUSE_WHEEL;
            event.timestamp = SDLevent.wheel.timestamp;
            event.mouseWheel.wheelX = SDLevent.wheel.x;
            event.mouseWheel.wheelY = SDLevent.wheel.y;
            event.mouseWheel.wheelTickX = SDLevent.wheel.x;
            event.mouseWheel.wheelTickY = SDLevent.wheel.y;
            break;
        }
        for (auto& listener : listeners)
            listener(event, deltaTime);
    } 
}

//void FE::InputHandler::DispatchEvents(float deltaTime)
//{
//}

void FE::InputHandler::RegisterListener(Listener listener)
{
    listeners.emplace_back(listener);
}
