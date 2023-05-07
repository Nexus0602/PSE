#include "Nexus.hh"

int main(int argc, char *args[]){

    Nexus engine = Nexus (800,800);

    const auto tree = engine.world.create();
    engine.world.emplace<TransformComponent>(tree, Vec2(400.0,400.0));
    engine.world.emplace<SpriteComponent>(tree, "tree",106,80);

    while (engine.NextFrame()){
        engine.Update();

        auto& treeTransform = engine.world.get<TransformComponent>(tree);
        treeTransform.rotation+=1;

        engine.Render();

    }

}