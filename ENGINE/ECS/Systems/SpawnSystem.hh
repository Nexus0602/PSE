#include <random>

class SpawnSystem {
    public:
        void OnKeyDown(const KeyDownEvent& keyDown) noexcept {
    int min = 0;
    int max = 800;

    // Crea el generador de números aleatorios y la distribución
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);

    CircleShape c = CircleShape(20,Color::Blue(),false);
    CircleShape c1 = CircleShape(20,Color::Green(),true);
    RectangleShape r = RectangleShape(40,30,Color::White(),true);
    RectangleShape r1  = RectangleShape(40,30,Color::Yellow(),false);

    const auto ent = keyDown.world->create();

    switch (keyDown.symbol){
        case SDLK_UP:
            keyDown.world->emplace<TransformComponent>(ent, Vec2(dis(gen),dis(gen)));
            keyDown.world->emplace<KinematicComponent>(ent);
            keyDown.world->emplace<RigidBodyComponent>(ent,1,c);
        break;
        case SDLK_RIGHT:
            keyDown.world->emplace<TransformComponent>(ent, Vec2(dis(gen),dis(gen)));
            keyDown.world->emplace<KinematicComponent>(ent);
            keyDown.world->emplace<RigidBodyComponent>(ent,1,c1);
        break;
        case SDLK_DOWN:
            keyDown.world->emplace<TransformComponent>(ent, Vec2(dis(gen),dis(gen)));
            keyDown.world->emplace<KinematicComponent>(ent);
            keyDown.world->emplace<RigidBodyComponent>(ent,1,r);
        break;
        case SDLK_LEFT:
            keyDown.world->emplace<TransformComponent>(ent, Vec2(dis(gen),dis(gen)));
            keyDown.world->emplace<KinematicComponent>(ent);
            keyDown.world->emplace<RigidBodyComponent>(ent,1,r1);
        break;
    }
}


};