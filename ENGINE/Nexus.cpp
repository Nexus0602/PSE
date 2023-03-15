#include "Nexus.hh"

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
            if (event.key.keysym.sym == SDLK_ESCAPE)
                running = false;
            if (event.key.keysym.sym == SDLK_UP)
                running = true;
            if (event.key.keysym.sym == SDLK_DOWN)
                running = true;

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

    Graphics::RenderFrame();
}

double Nexus::GetDeltaTime(int *last_frame_time){
    dt = (SDL_GetTicks() - *last_frame_time) / 1000.0f;
    *last_frame_time = SDL_GetTicks();
    return dt;


}

int Nexus::GetTotalTimeInMilliSeconds(){
    // hacer
    return 0;
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
