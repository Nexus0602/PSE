#include "Nexus.hh"

Nexus::Nexus(int width, int height){

    this->width = width;
    this->height = height;
    Logger::Info("Nexus constructor called.");

    //Setting core variables
    running = false;
    keyboard = new Keyboard();

    //Graphics initialization
    if (Graphics::OpenWindow(width,height))
        Logger::Info("Graphics initialized");

    eventBus.sink<KeyDownEvent>().connect<&GridMovementSystem::OnKeyDown>(gridMovementSystem);
    eventBus.sink<CollisionEvent>().connect<&DamageSystem::OnCollision>(damageSystem);

    //Adding assets to the manager
    Graphics::Addtexture("bcar","./ENGINE/assets/png/bluecar.png");
    Graphics::Addtexture("gcar","./ENGINE/assets/png/greencar.png");
    Graphics::Addtexture("bcar2","./ENGINE/assets/png/bluecar2.png");
    Graphics::Addtexture("gcar2","./ENGINE/assets/png/greencar2.png");
    Graphics::Addtexture("frog","./ENGINE/assets/png/frog.png");
    Graphics::Addtexture("nenufar","./ENGINE/assets/png/nenufar1.png");
    Graphics::Addtexture("nenufar2","./ENGINE/assets/png/nenufar2.png");
    Graphics::Addtexture("nenufar3","./ENGINE/assets/png/nenufar3.png");
    Graphics::Addtexture("nenufar4","./ENGINE/assets/png/nenufar4.png");
    Graphics::Addtexture("road","./ENGINE/assets/png/road.png");
    Graphics::Addtexture("lives0","./ENGINE/assets/png/vidas.png");
    Graphics::Addtexture("lives1","./ENGINE/assets/png/vidas1.png");
    Graphics::Addtexture("lives2","./ENGINE/assets/png/vidas2.png");
    Graphics::Addtexture("lives3","./ENGINE/assets/png/vidas3.png");
    Graphics::Addtexture("lives4","./ENGINE/assets/png/vidas4.png");
    Graphics::Addtexture("lives5","./ENGINE/assets/png/vidas5.png");
    Graphics::Addtexture("win","./ENGINE/assets/png/win.png");
    Graphics::Addtexture("lose","./ENGINE/assets/png/lose.png");
    Graphics::Addtexture("river","./ENGINE/assets/png/river.png");
    Graphics::Addtexture("rip","./ENGINE/assets/png/rip.png");

    // adding sound effects
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    std::cout<< Mix_GetError() << std::endl;
                }

    splashEffect = Mix_LoadWAV("./ENGINE/assets/sounds/splash2.wav");
    if (splashEffect == nullptr) {
        std::cout<<"Error"<<std::endl;
        }
    carEffect = Mix_LoadWAV("./ENGINE/assets/sounds/horn.wav");
    if (splashEffect == nullptr) {
        std::cout<<"Error"<<std::endl;
    }
    winEffect = Mix_LoadWAV("./ENGINE/assets/sounds/win.wav");
    if (winEffect == nullptr) {
        std::cout<<"Error"<<std::endl;
    }
    Mix_VolumeChunk(winEffect, MIX_MAX_VOLUME / 10);
    loseEffect = Mix_LoadWAV("./ENGINE/assets/sounds/lose.wav");
    if (loseEffect == nullptr) {
        std::cout<<"Error"<<std::endl;
    }
    Mix_VolumeChunk(loseEffect, MIX_MAX_VOLUME / 10);

    //adding a text font
    font = TTF_OpenFont("./ENGINE/assets/fonts/ALLSB.TTF", 50);
    if ( !font ) {
        std::cout << "Error loading font: " << TTF_GetError() << std::endl;
    }

    running = true;
}

Nexus::~Nexus(){
    Logger::Info("Nexus deconstructor called.");
    Mix_FreeChunk(splashEffect);
    Mix_FreeChunk(carEffect);
    Mix_FreeChunk(winEffect);
    Mix_FreeChunk(loseEffect);
    Graphics::CloseWindow();
}
void Nexus::Start(){

}

bool Nexus::NextFrame(){
    Graphics::CleanUpScreen();
    dt = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();

    return running;
}

void Nexus::Update(){
    CheckInput();

    //Updating Systems
    kinematicSystem.Update(dt,world);
    rigidBodySystem.Update(dt,world);
    collisionSystem.Update(eventBus, world);
    soundSystem.Update(dt,world);

}


void Nexus::CheckInput(){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:
            running=false;
            break;
            
            case SDL_KEYDOWN:
            eventBus.trigger(KeyDownEvent(event.key.keysym.sym, world));
            if (event.key.keysym.sym == SDLK_ESCAPE)
                running = false;
            break;
            
        }
    }
}

void Nexus::Render(){

    // rendering systems
    rigidBodySystem.Render(world);
    collisionSystem.Render(world);
    spriteSystem.Render(world);
    textSystem.Render(Graphics::renderer,world);
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


