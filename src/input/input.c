#include "input.h"

Input *Input_create() {
    Input *input = calloc(1, sizeof(Input));
    check(input != NULL, "Couldn't create Input");
    int i = 0;
    for (i = 0; i < 4; i++) {
        input->controllers[i] = Controller_create();
    }
    Input_reset(input);
    return input;
error:
    return NULL;
}

void Input_destroy(Input *input) {
    int i = 0;
    for (i = 0; i < 4; i++) {
        Controller *controller = input->controllers[i];
        Controller_destroy(controller);
    }
    free(input);
}

void Input_poll(Input *input) {
#ifdef DABES_IOS
  return;
#else
    // Hold keys
    Uint8 *keystate = SDL_GetKeyState(NULL);
    input->cam_zoom = 0;
    if (keystate[SDLK_j]) input->cam_zoom += 1;
    if (keystate[SDLK_k]) input->cam_zoom -= 1;

    input->cam_rotate = 0;
    if (keystate[SDLK_u]) input->cam_rotate += 1;
    if (keystate[SDLK_i]) input->cam_rotate -= 1;

    input->controllers[0]->dpad = CONTROLLER_DPAD_NONE;
    if (keystate[SDLK_UP])
        input->controllers[0]->dpad |= CONTROLLER_DPAD_UP;
    if (keystate[SDLK_DOWN])
        input->controllers[0]->dpad |= CONTROLLER_DPAD_DOWN;
    if (keystate[SDLK_LEFT])
        input->controllers[0]->dpad |= CONTROLLER_DPAD_LEFT;
    if (keystate[SDLK_RIGHT])
        input->controllers[0]->dpad |= CONTROLLER_DPAD_RIGHT;
    if (keystate[SDLK_SPACE])
        input->controllers[0]->jump = 1;

    // Momentary keys
    SDL_Event event = {};
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_q) input->game_quit = 1;
            if (event.key.keysym.sym == SDLK_r) input->cam_reset = 1;
            if (event.key.keysym.sym == SDLK_g)
                input->debug_scene_draw_grid = 1;
            if (event.key.keysym.sym == SDLK_c)
                input->cam_debug = 1;
            if (event.key.keysym.sym == SDLK_p)
                input->phys_render = 1;
        }
    }
#endif
}

void Input_touch(Input *input, Input *touch_input) {
    int i = 0;
    input->game_quit = touch_input->game_quit;
    input->debug_scene_draw_grid = touch_input->debug_scene_draw_grid;
    input->cam_reset = touch_input->cam_reset;
    input->cam_zoom = touch_input->cam_zoom;
    input->cam_rotate = touch_input->cam_rotate;

    for (i = 0; i < 4; i++) {
        input->controllers[i]->dpad = touch_input->controllers[i]->dpad;
        input->controllers[i]->jump = touch_input->controllers[i]->jump;
    }
}

void Input_reset(Input *input) {
    check_mem(input);
    input->game_quit = 0;
    input->debug_scene_draw_grid = 0;
    input->cam_reset = 0;
    input->cam_zoom = 0;
    input->cam_rotate = 0;
    input->cam_debug = 0;
    input->phys_render = 0;
    int i = 0;
    for (i = 0; i < 4; i++) {
        Controller *controller = input->controllers[i];
        Controller_reset(controller);
    }
    return;
error:
    return;
}

