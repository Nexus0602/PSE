#include "Nexus.hh"

int main(int argc, char *args[]){

    Nexus engine = Nexus(800,800);

    /*const auto frog=engine.world.create();
    engine.world.emplace<TransformComponent>(frog,Vec2(400,300));
    engine.world.emplace<SpriteComponent>(frog,"frog",132,400);
    engine.world.emplace<AnimationComponent>(frog,5,4,true);*/

    const auto dog=engine.world.create();
    engine.world.emplace<TransformComponent>(dog,Vec2(400,400));
    engine.world.emplace<SpriteComponent>(dog,"dog",181,153);
    engine.world.emplace<AnimationComponent>(dog,9,6,true);

    /*const auto cat=engine.world.create();
    engine.world.emplace<TransformComponent>(cat,Vec2(400,200));
    engine.world.emplace<SpriteComponent>(cat,"cat",240,184);
    engine.world.emplace<AnimationComponent>(cat,8,6,true);*/

    const auto cat=engine.world.create();
    engine.world.emplace<TransformComponent>(cat,Vec2(400,200),0.0,Vec2(2.5,2.5));
    engine.world.emplace<SpriteComponent>(cat,"gato",60,86);
    engine.world.emplace<AnimationComponent>(cat,4,6,true);


    vector<entt::entity> coins;
    int totalCoins = 5;
    int x = 100;
    for (int i = 0; i<totalCoins; i++){
    const auto coin=engine.world.create();
    engine.world.emplace<TransformComponent>(coin,Vec2(x,600),0.0,Vec2(0.8,0.8));
    engine.world.emplace<SpriteComponent>(coin,"coin",125,242);
    engine.world.emplace<AnimationComponent>(coin,9,10,true);
    x+=150;
    }



    while(engine.NextFrame()){
        engine.Update();
        Graphics::DrawFillRect(400,400,800,800,Color::color(255,255,255));
        engine.Render();
    }

    return 0;
}