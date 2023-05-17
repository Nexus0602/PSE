#include "Keyboard.hh"
#include "Color.hh"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "Logger.hh"
#include "Graphics.hh"
#include "Vec2.hh"
#include <iostream>
#include <stdbool.h>

#include "entt/entt.hpp" //no tocar, siempre antes que ECS

#include "Events/KeyDownEvent.hh"
#include "Events/CollisionEvent.hh"

#include "ECS/Components/NameGroup.hh"
#include "ECS/Components/Transform.hh"
#include "ECS/Components/Kinematic.hh"
#include "ECS/Components/Shape.hh"
#include "ECS/Components/CircleShape.hh"
#include "ECS/Components/PolygonShape.hh"
#include "ECS/Components/RectangleShape.hh"
#include "ECS/Components/RigidBody.hh"
#include "ECS/Components/GridMovement.hh"
#include "Collisions.hh"
#include "ECS/Components/Collider.hh"
#include "ECS/Components/Health.hh"
#include "ECS/Components/Sprite.hh"
#include "ECS/Components/Sound.hh"
#include "ECS/Components/Text.hh"


#include "ECS/Systems/KinematicSystem.hh"
#include "ECS/Systems/RigidBodySystem.hh"
#include "ECS/Systems/GridMovementSystem.hh"
#include "ECS/Systems/CollisionSystem.hh"
#include "ECS/Systems/DamageSystem.hh"
#include "ECS/Systems/SpriteSystem.hh"
#include "ECS/Systems/AnimationSystem.hh"
#include "ECS/Systems/SoundSystem.hh"
#include "ECS/Systems/TextSystem.hh"



class Nexus {
    private:
    // Game loop
    //bool debug = false;
    bool running = false;
    double dt = 0;
    int last_frame_time = 0; // ms

    public:
    int width, height;
    Nexus(int width, int height);
    ~Nexus();

    //sound effects
    Mix_Chunk* splashEffect;
    Mix_Chunk* carEffect;
    Mix_Chunk* winEffect;
    Mix_Chunk* loseEffect;

    //text font
    TTF_Font* font ;

    //Input 
    Keyboard* keyboard;

    //Game loop
    void Start();
    bool NextFrame();
    void CheckInput();
    void Update();
    void Render();
    double GetDeltaTime();
    int GetTotalTimeInMilliSeconds();


    //EnTT (ECS)
    entt::registry world;
    entt::dispatcher eventBus; 

    //Systems
    KinematicSystem kinematicSystem;
    RigidBodySystem rigidBodySystem;
    GridMovementSystem gridMovementSystem;
    CollisionSystem collisionSystem;
    DamageSystem damageSystem;
    SpriteSystem spriteSystem;
    SoundSystem soundSystem;
    TextSystem textSystem;
    AnimationSystem animationSystem;
};