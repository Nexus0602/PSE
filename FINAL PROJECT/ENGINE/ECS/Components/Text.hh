#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <string>

// Componente de texto
struct TextComponent
{
    std::string text;
    SDL_Color color;
    TTF_Font* font ;
    SDL_Texture* texture = nullptr;
    int x;
    int y;

    TextComponent (std::string text,SDL_Color color, TTF_Font* font, int x = 0, int y = 0){
        this->text = text;
        this->color = color;
        this->font = font;
        this->x =x;
        this->y=y;

    }
};