#include "Nexus.hh"

int main(int argc, char *argv[]){

    Nexus engine = Nexus(800,800);

    const auto ball = engine.world.create();
    engine.world.emplace<TransformComponent>(ball, Vec2(400,400));
    engine.world.emplace<GridMovementComponent>(ball,100);

    while(engine.NextFrame()){
        engine.Update();

        Graphics::DrawGrid(100);
        const auto transform = engine.world.get<TransformComponent>(ball);
        Graphics::DrawFillCircle(
            transform.position.x,
            transform.position.y,
            25,
            Color::White()
        );
        engine.Render();
    }

    return 0;
}