#include <iostream>
#include <stdbool.h>
#include <SDL2/SDL.h>

/** 
 * @brief 
 * Function declaration
 */
void destroy();
bool graphicsinitialization(int width, int height);
void process_input(bool *game_is_running);
void update();
void render();
bool game_running=false;

//int player_x=20;
//int player_y=20;
//int dx = 1;
//int dy = 1;

/** 
 * @brief 
 * Global variables
 */
struct {
    int x = 20 ;
    int y = 20 ;
} player;

struct{
    int x = 1 ;
    int y = 1 ; 
} d;

SDL_Event sdl_event;
SDL_Window* window;
SDL_Renderer* renderer;

/** 
 * @brief 
 * Main
 * @param argc 
 * @param argv 
 * @return int 
 */
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

/** 
 * @brief 
 * Destroy function
 * Destroys renderer and window
 */
void destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Graphichs destroyed" << std::endl;
}

/**
 * @brief 
 * Graphic initialization function
 * Creates window and renderer
 * @param width 
 * @param height 
 * @return true 
 * @return false 
 */
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

/**
 * @brief 
 * Process input function
 * Processes the user input
 * @param game_is_running 
 */
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

/**
 * @brief 
 * Update function
 * Updates player position (both x and y)
 */
void update()
{
    if (player.x > 640 - 10 || player.x < 0) {
        d.x = -d.x;
    }
    if (player.y > 400 - 10 || player.y < 0) {
        d.y = -d.y;
    }
    player.x += d.x;
    player.y += d.y;
}

/**
 * @brief
 * Render function
 * Defines and updates variables related to render
 */
void render()
{
    SDL_SetRenderDrawColor(renderer,30,30,30,255);
    SDL_RenderClear(renderer);

    SDL_Rect box = {player.x, player.y, 10,10};
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderFillRect(renderer, &box);

    SDL_RenderPresent(renderer);
}