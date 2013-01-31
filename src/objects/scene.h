#ifndef __scene_h
#define __scene_h
#include "../prefix.h"
#include "game_entity.h"
#include "world.h"

typedef struct Scene {
    Object proto;
    GLuint bg_texture;

    Mix_Music *music;

    float projection_scale;
    float projection_rotation;

    GameEntity *entities[256];
} Scene;

int Scene_init(void *self);
void Scene_destroy(void *self);
void Scene_render(void *self, void *engine);
World *Scene_create_world(Scene *scene, Physics *physics);

extern Object SceneProto;

#endif
