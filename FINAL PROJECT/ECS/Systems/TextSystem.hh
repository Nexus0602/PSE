#include <SDL2/SDL_ttf.h>
#include <string>
class TextSystem
{
public:

    void Render(SDL_Renderer* renderer, entt::registry& world){
        auto view = world.view<TextComponent>();
        for(auto entity:view){
            auto& text = view.get<TextComponent>(entity);
    
        SDL_Surface* surface = TTF_RenderText_Blended(text.font, text.text.c_str(), text.color);
        //std::cout<<"HOLA"<<std::endl;
        if (surface == nullptr)
        {
            // Manejar error de renderización de texto
            SDL_Log("Error al renderizar texto: %s", TTF_GetError());
            // Puedes agregar cualquier manejo de errores adicional aquí
        }
        else
        {
            text.texture = SDL_CreateTextureFromSurface(renderer, surface);
            //std::cout<<"HOLA2"<<std::endl;

            if (text.texture == nullptr)
            {
                // Manejar error de creación de textura
                SDL_Log("Error al crear textura de texto: %s", SDL_GetError());
                // Puedes agregar cualquier manejo de errores adicional aquí
            }
            else
            {
                SDL_Rect dstRect = { text.x, text.y, surface->w, surface->h };
                SDL_RenderCopy(renderer, text.texture, nullptr, &dstRect);
            }
            SDL_FreeSurface(surface);
        }
    }
    }
};