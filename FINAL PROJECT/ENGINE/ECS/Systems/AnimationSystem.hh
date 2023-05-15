/* ALLOWS CREATING ANIMATIONS FROM AN ARRAY OF SPRITES */

class AnimationSystem{

    public:
        void Render(entt::registry& world){
            auto view=world.view<SpriteComponent,AnimationComponent>();
            for(auto entity:view){

                auto& a=view.get<AnimationComponent>(entity);
                auto& s=view.get<SpriteComponent>(entity);

                int currentFrame=((SDL_GetTicks()-a.startTime)* a.frameSpeedRate/1000);
                int moduledCurrentFrame=currentFrame % a.numFrames;

                if(currentFrame>= a.numFrames && !a.isLoop){

                    moduledCurrentFrame= a.numFrames -1;

                }

                a.currentFrame= moduledCurrentFrame;
                s.srcRect.x=a.currentFrame * s.width;

            }

        }



};