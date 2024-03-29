#include "Graphics.hh"
#include "Logger.hh"
#include <iostream>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <map>

SDL_Window *Graphics::window = NULL;
SDL_Renderer *Graphics::renderer = NULL;

int Graphics::windowWidth, Graphics::windowHeight = 0;
static std::map<std::string, SDL_Texture*> textures;

bool Graphics::OpenWindow(int width, int height)
{
    windowWidth = width;
    windowHeight = height;


    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        Logger::Error("Error initializing SDL.");
        return false;
    }

    window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_BORDERLESS);
    if (!window)
    {
        Logger::Error("Error creating SDL window.");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        Logger::Error("Error creating SDL renderer.");
        return false;
    }
    if ( TTF_Init() < 0 ) {
        std::cout << "Error intializing SDL_ttf: " << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}

void Graphics::CloseWindow()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Graphics::ClearAssets();
    TTF_Quit();
    SDL_Quit();
    Logger::Info("Graphics terminated.");
}

void Graphics::CleanUpScreen()
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Graphics::RenderFrame()
{
    SDL_RenderPresent(renderer);
}

void Graphics::DrawLine(int x0, int y0, int x1, int y1, Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, x0, y0, x1, y1);
}

void Graphics::DrawRect(int x, int y, int width, int height, Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect box = {x - width / 2, y - height / 2, width, height};
    SDL_RenderDrawRect(renderer, &box);
}

void Graphics::DrawCircle(int x0, int y0, int radius, Color color, float angle = 0.0)
{

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        // Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, x0 + x, y0 - y);
        SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
        SDL_RenderDrawPoint(renderer, x0 - x, y0 - y);
        SDL_RenderDrawPoint(renderer, x0 - x, y0 + y);
        SDL_RenderDrawPoint(renderer, x0 + y, y0 - x);
        SDL_RenderDrawPoint(renderer, x0 + y, y0 + x);
        SDL_RenderDrawPoint(renderer, x0 - y, y0 - x);
        SDL_RenderDrawPoint(renderer, x0 - y, y0 + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }

    SDL_RenderDrawLine(renderer, x0, y0, x0 + cos(angle) * radius, y0 + sin(angle) * radius);
}

void Graphics::DrawFillCircle(int x0, int y0, int radius, Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        // Each of the following renders an octant of the circle
        SDL_RenderDrawLine(renderer,x0 + x, y0 - y, x0 + x, y0 + y);
        SDL_RenderDrawLine(renderer,x0 - x, y0 - y, x0 - x, y0 + y);
        SDL_RenderDrawLine(renderer,x0 + y, y0 - x, x0 + y, y0 + x);
        SDL_RenderDrawLine(renderer,x0 - y, y0 - x, x0 - y, y0 + x);


        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void Graphics::DrawFillRect(int x, int y, int width, int height, Color color)
{
SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
SDL_Rect box = {x - width / 2, y - height / 2, width, height};
SDL_RenderDrawRect(renderer, &box);
SDL_RenderFillRect(renderer, &box);
}

void Graphics::DrawGrid(int cell_size){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Establecer color de fondo a negro
    SDL_RenderClear(renderer); // Limpiar pantalla con el color de fondo

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Establecer color de línea a blanco


        int grid_size = 10; // tamaño de cuadrícula

        for (int i = 0; i <= grid_size; i++) {
            // línea vertical
            SDL_RenderDrawLine(renderer, i * cell_size, 0, i * cell_size, cell_size * grid_size);
            // línea horizontal
            SDL_RenderDrawLine(renderer, 0, i * cell_size, cell_size * grid_size, i * cell_size);
        }

}

void Graphics::DrawPolygon(int x, int y, const std::vector<Vec2>& vertices, Color color){


    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Crear un array de SDL_Point con los vértices del polígono
    std::vector<SDL_Point> points;
    for (const auto& vertex : vertices) {
        points.push_back({x + static_cast<int>(vertex.x),
                        y + static_cast<int>(vertex.y)});
    }

    // Dibujar el polígono
    SDL_RenderDrawLines(renderer, &points[0], points.size());
    SDL_RenderDrawLine(renderer,points[points.size()-1].x,points[points.size()-1].y, points[0].x,points[0].y);
}

void Graphics::DrawSprite(SDL_Texture* texture, Vec2 position, Vec2 scale, int width, int height, float rotation, SDL_Rect _srcRect ){
    SDL_Rect srcRect = _srcRect;

    SDL_Rect dstRect = {
        static_cast<int>(position.x - width * scale.x * 0.5),
        static_cast<int>(position.y - height * scale.y * 0.5),
        static_cast<int>(width*scale.x),
        static_cast<int>(height*scale.y)
    };


    if (SDL_RenderCopyEx(renderer,texture,&srcRect,&dstRect,rotation,NULL,SDL_FLIP_NONE)!=0){
        std::cout << "Error rendering sprite " << SDL_GetError()<<std::endl;
    }
}

void Graphics::ClearAssets(){

    for (auto texture: textures) {
        SDL_DestroyTexture(texture.second);
    }
    textures.clear();

}


void Graphics::Addtexture(const std::string& assetId, const std::string& filePath) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (surface == nullptr) {
        std::cout << "IMG_Load Error: " << IMG_GetError() << std::endl;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
    if (texture == nullptr) {
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(surface);

    textures.emplace(assetId, texture);

    Logger::Info("Texture added whith id " + assetId);

}

SDL_Texture* Graphics::GetTexture(const std::string& assetId){

    return textures[assetId];

}



