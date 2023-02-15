#include <iostream>
#include <stdbool.h>
#include <SDL2/SDL.h>

void destroy();
bool graphicsinitialization(int width, int height);
void process_input(bool *game_is_running);
void update();
void render();


#define FPS 20
#define FRAME_TARGET_TIME (1000/FPS)
int last_frame_time=0;
int speed_x = 120;
int speed_y = 120;
bool game_running=false;
int player_x=20;
int player_y=20;
SDL_Event sdl_event;
SDL_Window* window;
SDL_Renderer* renderer;


int main(int argc, char** argv)
{
    game_running = graphicsinitialization(640,400);
    while(game_running)
    {
        process_input(&game_running);
        update();
        render();
    }
    destroy();
    return 0;
}



void destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Graphichs destroyed" << std::endl;
}
bool graphicsinitialization(int width, int height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) !=0)
    {
        std::cerr << "Error initializing SDL" << std::endl;
        return false;
    }
    window = SDL_CreateWindow
    (
        "My first window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN

    );
    if(!window)
    {
        std::cerr << "Error creating SDL windows" << std:: endl;
        return false;
    }

    renderer = SDL_CreateRenderer
    (
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!renderer)
    {
        std:: cerr<< "Error creating SDL renderer" << std::endl;
        return false;
    }
    std::cout << "Graphics initialized" << std::endl;

    return true;
}

void process_input(bool *game_is_running)
{
    SDL_PollEvent(&sdl_event);
    switch (sdl_event.type)
    {
    case SDL_QUIT:
        *game_is_running =false;
        break;
    case SDL_KEYDOWN:
        if(sdl_event.key.keysym.sym == SDLK_ESCAPE)
            *game_is_running=false;
        break;
    }

}
void update()
{
    int delta_time_ms =  (SDL_GetTicks() - last_frame_time);

    float delta_time = delta_time_ms / 1000.0f;
    //std::cout << delta_time ;

    if (player_x > 640 - 10 || player_x < 0) {
        speed_x = -speed_x;
    }
    if (player_y > 400 - 10 || player_y < 0) {
        speed_y = -speed_y;
    }

    player_x += speed_x * delta_time;
    player_y += speed_y * delta_time;

    last_frame_time = SDL_GetTicks();

}
void render()
{
    SDL_SetRenderDrawColor(renderer,30,30,30,255);
    SDL_RenderClear(renderer);

    SDL_Rect box = {player_x, player_y, 10,10};
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderFillRect(renderer, &box);

    SDL_RenderPresent(renderer);
}