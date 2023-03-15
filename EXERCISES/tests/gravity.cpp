#include "Nexus.hh"

int main(int argc, char *args[]){
    Nexus engine = Nexus (800,800);

    const auto ball = engine.world.create();

    engine.world.emplace<TransformComponent>(ball, Vec2(400.0,400.0));
    engine.world.emplace<KinematicComponent>(ball, Vec2(0, -200), Vec2 (0,100));

    while (engine.NextFrame()){
        engine.Update();

        const auto transform = engine.world.get<TransformComponent>(ball);
        engine.DrawFillCircle(transform.position.x, transform.position.y, 40, Color::Blue());
        
        engine.Render();
        }

    return 0;
}