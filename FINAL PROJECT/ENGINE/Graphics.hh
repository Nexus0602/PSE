#include "Color.hh"
#include "Vec2.hh"
#include <SDL2/SDL.h>

class Graphics {
    private:
    static int windowWidth;
    static int windowHeight;
    static SDL_Window* window;
    public:
    static SDL_Renderer* renderer;

    public:
    static bool OpenWindow(int width, int height);
    static void CloseWindow();
    static void RenderFrame();
    static void CleanUpScreen();

    static void DrawLine(int x0, int y0, int x1, int y1, Color color);
    static void DrawCircle(int x, int y, int radius, Color color, float angle);
    static void DrawFillCircle(int x, int y, int radius, Color color);
    static void DrawRect(int x, int y, int width, int height, Color color);
    static void DrawFillRect(int x, int y, int width, int height, Color color);
    static void DrawGrid(int);
    static void DrawPolygon(int x, int y, const std::vector<Vec2>& vertices, Color color);

    static void DrawSprite(SDL_Texture* texture, Vec2 position, Vec2 scale, int width, int height, float rotation, SDL_Rect srcRect );

    //Asset manager
    static void ClearAssets();
    static void Addtexture(const std::string& assetId, const std::string& filePath);
    static SDL_Texture* GetTexture(const std::string& assetId);

    static void Text();
};