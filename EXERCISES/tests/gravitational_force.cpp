#include "Nexus.hh"

int main(int argc, char *args[]){

    int width = 800;
    int height = 800;
    Nexus engine = Nexus (width,height);

    const auto earth = engine.world.create();
    engine.world.emplace<TransformComponent>(earth,Vec2(100.0,100.0));
    engine.world.emplace<KinematicComponent>(earth,Vec2(150,0),Vec2 (0,0));
    engine.world.emplace<ParticleComponent>(earth,1, 10, Color::Blue());

    const auto sun = engine.world.create();
    engine.world.emplace<TransformComponent>(sun,Vec2(width/2,height/2));
    engine.world.emplace<KinematicComponent>(sun,Vec2(0,0),Vec2 (0,0));
    engine.world.emplace<ParticleComponent>(sun,20, 30, Color::Yellow());

    auto&tEarth = engine.world.get<TransformComponent>(earth);
    auto&pEarth = engine.world.get<ParticleComponent>(earth);

    auto&tSun = engine.world.get<TransformComponent>(sun);
    auto&pSun = engine.world.get<ParticleComponent>(sun);

    while(engine.NextFrame()){
        engine.Update();

        Vec2 gravitationalForce = Force::GenerateGravitationalVector(tEarth.position, tSun.position,pEarth.mass, pSun.mass, 1000 , 5, 100);
        pEarth.AddForce(gravitationalForce);
        pSun.AddForce(-gravitationalForce);

        engine.Render();

    }

    return 0;

}