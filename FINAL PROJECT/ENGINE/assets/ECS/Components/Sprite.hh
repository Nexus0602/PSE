struct SpriteComponent {

    std::string assetId;
    int width;
    int height;
    SDL_Rect srcRect;

    SpriteComponent (std::string assetId = "", int width = 0 , int height = 0, int rectX = 0, int rectY = 0 ){
        this->assetId = assetId;
        this->width = width;
        this->height = height;
        this->srcRect = {rectX,rectY,width,height};
    }

};

struct AnimationComponent{

    int numFrames;
    int currentFrame;
    int frameSpeedRate;
    bool isLoop;
    int startTime;

    AnimationComponent(int numFrames = 1, int frameSpeedRate = 1, bool isLoop = true ){
        this->numFrames = numFrames;
        this->currentFrame = 0;
        this->frameSpeedRate = frameSpeedRate;
        this->isLoop = isLoop;
        this->startTime = SDL_GetTicks();

    }
    
};