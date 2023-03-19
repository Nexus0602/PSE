#include "Nexus.hh"

int main(int argc, char *args[]){

    Nexus engine = Nexus (800,800);

    Vec2 smallWindForce = Vec2(2,0);
    Vec2 bigWindForce = Vec2(4,0);

    const auto smallBall = engine.world.create();
    engine.world.emplace<TransformComponent>(smallBall,Vec2(100,700));
    engine.world.emplace<KinematicComponent>(smallBall,Vec2(0,-30),Vec2 (0,0));
    engine.world.emplace<ParticleComponent>(smallBall,1, 10);

    const auto bigBall = engine.world.create();
    engine.world.emplace<TransformComponent>(bigBall,Vec2(200,700));
    engine.world.emplace<KinematicComponent>(bigBall,Vec2(0,-30),Vec2 (0,0));
    engine.world.emplace<ParticleComponent>(bigBall,5, 20, Color::Green());

    auto&smallParticleComponent = engine.world.get<ParticleComponent>(smallBall);
    auto&bigParticleComponent = engine.world.get<ParticleComponent>(bigBall);

    while(engine.NextFrame()){
        engine.Update();

        //Graphics::DrawGrid(100);

        smallParticleComponent.AddForce(Vec2(2,-8));
        bigParticleComponent.AddForce(Vec2(4,-4));

        engine.Render();

    }

    return 0;

}