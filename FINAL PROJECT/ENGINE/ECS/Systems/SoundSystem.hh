#include <SDL2/SDL_mixer.h>
struct SoundSystem {
    void Update(const double dt, entt::registry& world) {
        auto view = world.view<SoundComponent>();
        for(auto entity:view){
            auto& sound = view.get<SoundComponent>(entity);
        if (sound.shouldPlay) {
            Mix_PlayChannel(-1, sound.soundEffect, 0);
            sound.shouldPlay = false;
        }
        }
    }
};