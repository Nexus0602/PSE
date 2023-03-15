#include "Mouse.hh"
#include "Keyboard.hh"
#include "Color.hh"
#include <SDL2/SDL.h>
#include "Logger.hh"
#include "Graphics.hh"
#include "Vec2.hh"
#include <iostream>
#include <stdbool.h>
#include "ECS/Components/Transform.hh"
#include "entt/entt.hpp"
#include "ECS/Systems/KinematicSystem.hh"

class Nexus {
    private:
    // Game loop
    bool debug = false;
    bool running = false;
    double dt = 0;
    int last_frame_time = 0; // ms

    public:
    int width, height;
    Nexus(int width, int height);
    ~Nexus();

    //Input 
    Mouse* mouse;
    Keyboard* keyboard;

    //Game loop
    void Start();
    bool NextFrame();
    void CheckInput();
    Vec2 CheckMousePos();
    void Update();
    void Render();
    double GetDeltaTime(int *lft);
    int GetTotalTimeInMilliSeconds();
    double GetTotalTimeInSeconds();
    void DrawRect(int x, int y, int width, int height, Color color);
    void DrawFillRect(int x, int y, int width, int height, Color color);
    void DrawCircle(int x, int y, int radius, Color color, float angle);
    void DrawFillCircle(int x, int y, int radius, Color color);

    //EnTT (ECS)
    entt::registry world;

    //Systems
    KinematicSystem kinematicSystem;
};