#include "Mouse.hh"
#include "Keyboard.hh"
#include "Color.hh"
#include <SDL2/SDL.h>
#include "Logger.hh"
#include "Graphics.hh"
#include "Vec2.hh"
#include "Force.hh"
#include <iostream>
#include <stdbool.h>

#include "entt/entt.hpp" //no tocar, siempre antes que ECS

#include "Events/KeyDownEvent.hh"

#include "ECS/Components/Transform.hh"
#include "ECS/Components/Kinematic.hh"
#include "ECS/Components/Particle.hh"
#include "ECS/Components/DragAndDrop.hh"
#include "ECS/Components/Shape.hh"
#include "ECS/Components/CircleShape.hh"
#include "ECS/Components/PolygonShape.hh"
#include "ECS/Components/RectangleShape.hh"
#include "ECS/Components/RigidBody.hh"
#include "ECS/Components/GridMovement.hh"
#include "ECS/Components/NameGroup.hh"

#include "ECS/Systems/KinematicSystem.hh"
#include "ECS/Systems/ParticleSystem.hh"
#include "ECS/Systems/DragAndDropSystem.hh"
#include "ECS/Systems/RigidBodySystem.hh"
#include "ECS/Systems/GridMovementSystem.hh"
#include "ECS/Systems/SpawnSystem.hh"

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
    entt::dispatcher eventBus;

    //Systems
    KinematicSystem kinematicSystem;
    ParticleSystem particleSystem;
    DragAndDropImpulseSystem dragAndDropSystem;
    RigidBodySystem rigidBodySystem;
    GridMovementSystem gridMovementSystem;
    SpawnSystem spawnSystem;
};