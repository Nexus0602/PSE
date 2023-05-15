#include <SDL2/SDL_mixer.h>

struct SoundComponent {
    Mix_Chunk* soundEffect;
    bool shouldPlay;

    SoundComponent(Mix_Chunk* soundEffect, bool shouldPlay = false ) : soundEffect(soundEffect), shouldPlay(shouldPlay) {}
};
