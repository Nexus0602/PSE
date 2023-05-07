#include "Nexus.hh"
#include <filesystem>


Nexus::Nexus(int width, int height){

    this->width = width;
    this->height = height;
    Logger::Info("Nexus constructor called.");

    //Setting core variables
    running = false;
    mouse = new Mouse();
    keyboard = new Keyboard();

    //Graphics initialization
    if (Graphics::OpenWindow(width,height))
        Logger::Info("Graphics initialized");

    eventBus.sink<KeyDownEvent>().connect<&GridMovementSystem::OnKeyDown>(gridMovementSystem);
    //eventBus.sink<KeyDownEvent>().connect<&SpawnSystem::OnKeyDown>(spawnSystem);
    //eventBus.sink<CollisionEvent>().connect<&CollisionSystem::OnCollision>(collisionSystem);
    eventBus.sink<CollisionEvent>().connect<&DamageSystem::OnCollision>(damageSystem);


    //Adding assets to the manager
    
    //Graphics::Addtexture("snoopy","./assets/png/sn.png");
    Graphics::Addtexture("tree","./../../ENGINE/assets/png/arbol.png");
    //Graphics::Addtexture("fire","./../../ENGINE/assets/png/fire.jpeg");
    //Graphics::Addtexture("frog","./../../ENGINE/assets/png/frog.png");
    Graphics::Addtexture("coin","./../../ENGINE/assets/png/coin.png");
    Graphics::Addtexture("dog","./../../ENGINE/assets/png/dog.png");
    Graphics::Addtexture("cat","./../../ENGINE/assets/png/cat.png");
    Graphics::Addtexture("gato","./../../ENGINE/assets/png/gato.png");


    running = true;
}

Nexus::~Nexus(){
    Logger::Info("Nexus deconstructor called.");
    Graphics::CloseWindow();
}
void Nexus::Start(){

}

bool Nexus::NextFrame(){
    Graphics::CleanUpScreen();
    dt = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    //dt = Nexus::GetDeltaTime(&last_frame_time);
    last_frame_time = SDL_GetTicks();
    return running;
}

void Nexus::Update(){
    CheckInput();

    //Systems
    kinematicSystem.Update(dt,world);
    particleSystem.Update(dt,world);
    dragAndDropSystem.Update(world);
    rigidBodySystem.Update(dt,world);
    collisionSystem.Update(eventBus, world);

}

Vec2 Nexus::CheckMousePos(){
    
    int x,y;
    SDL_GetMouseState(&x,&y);
    return Vec2(x,y);
}

void Nexus::CheckInput(){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:
            running=false;
            break;
            case SDL_MOUSEMOTION:
            {
                int x = event.motion.x;
                int y = event.motion.y;
                mouse->UpdatePosition(x,y);
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            int x,y;
            SDL_GetMouseState(&x,&y);
            mouse->UpdatePosition(x,y);
            if (event.button.button == SDL_BUTTON_LEFT)
            mouse->leftButtonPressed = true;
            if (event.button.button == SDL_BUTTON_RIGHT)
            mouse->rightButtonPressed = true;
            break;
            case SDL_KEYDOWN:
            eventBus.trigger(KeyDownEvent(event.key.keysym.sym, world));
            if (event.key.keysym.sym == SDLK_ESCAPE)
                running = false;
            break;
            
            /*
            if (event.key.keysym.sym == SDLK_UP){
                running = true;
                keyboard->upKeyPressed = true;
                }
            if (event.key.keysym.sym == SDLK_DOWN){
                running = true;
                keyboard->downKeyPressed = true;
                }*/

            // ...

            break;

            case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_F1)
                debug=!debug;
            if (event.key.keysym.sym == SDLK_UP)
                keyboard->upKeyPressed = false;
            if (event.key.keysym.sym == SDLK_DOWN)
                keyboard->upKeyPressed = false;

            // ... 
            break;
        }
    }
}

void Nexus::Render(){

    particleSystem.Render(world);
    rigidBodySystem.Render(world);
    collisionSystem.Render(world);
    spriteSystem.Render(world);
    animationSystem.Render(world);
    Graphics::RenderFrame();
}

double Nexus::GetDeltaTime(){
    dt = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();
    return dt;


}

int Nexus::GetTotalTimeInMilliSeconds(){
    
    return (SDL_GetTicks() - initial_time)/1000.0f ;
}

double Nexus::GetTotalTimeInSeconds(){
    // hacer
    return 0.0;
}

void Nexus::DrawRect(int x, int y, int width, int height, Color color){
    Graphics::DrawRect(x,y,width,height,color);
}

void Nexus::DrawFillRect(int x, int y, int width, int height, Color color){
    Graphics::DrawFillRect(x,y,width,height,color);
}

void Nexus::DrawCircle(int x, int y, int radius, Color color, float angle){
    Graphics::DrawCircle(x,y,radius,color,angle);
}

void Nexus::DrawFillCircle(int x, int y, int radius, Color color){
    Graphics::DrawFillCircle(x,y,radius,color);
}
