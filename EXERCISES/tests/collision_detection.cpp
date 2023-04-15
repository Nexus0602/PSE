#include "Nexus.hh"

int main(int argc, char *argv[]){

    Nexus engine = Nexus(800,800);
    

    auto a = engine.world.create();
    engine.world.emplace<TransformComponent>(a,Vec2(250,100));
    engine.world.emplace<KinematicComponent>(a,Vec2(0,150));
    RectangleShape r = RectangleShape(75 ,100,  Color::Blue(),true);
    engine.world.emplace<ColliderComponent>(a, r, true, 1);
    engine.world.emplace<NameGroupComponent>(a,"player ", "player");
    engine.world.emplace<HealthComponent>(a,50);

    auto c = engine.world.create();
    engine.world.emplace<TransformComponent>(c,Vec2(250,750));
    engine.world.emplace<KinematicComponent>(c,Vec2(0,0));
    RectangleShape r2 = RectangleShape(100,100, Color::Yellow(),true);
    engine.world.emplace<ColliderComponent>(c,r2, true, 10000);
    engine.world.emplace<NameGroupComponent>(c,"enemy2 ", "enemies");

    auto d = engine.world.create();
    engine.world.emplace<TransformComponent>(d,Vec2(250,50));
    engine.world.emplace<KinematicComponent>(d,Vec2(0,0));
    RectangleShape r3 = RectangleShape(100,100, Color::Yellow(),true);
    engine.world.emplace<ColliderComponent>(d,r3, true, 1000000);
    engine.world.emplace<NameGroupComponent>(d,"enemy2 ", "enemies");


    auto b = engine.world.create();
    engine.world.emplace<TransformComponent>(b,Vec2(500,100));
    engine.world.emplace<KinematicComponent>(b,Vec2(0,150));
    CircleShape c1 = CircleShape(35 ,Color::Blue(),true);
    engine.world.emplace<ColliderComponent>(b, c1, true, 1);
    engine.world.emplace<NameGroupComponent>(b,"player ", "player");
    engine.world.emplace<HealthComponent>(b,50);

    auto e = engine.world.create();
    engine.world.emplace<TransformComponent>(e,Vec2(500,750));
    engine.world.emplace<KinematicComponent>(e,Vec2(0,0));
    CircleShape circle2 = CircleShape(50 ,Color::Yellow(),true);
    engine.world.emplace<ColliderComponent>(e,circle2, true, 10000);
    engine.world.emplace<NameGroupComponent>(e,"enemy2 ", "enemies");

    auto f = engine.world.create();
    engine.world.emplace<TransformComponent>(f,Vec2(500,50));
    engine.world.emplace<KinematicComponent>(f,Vec2(0,0));
    CircleShape circle3 = CircleShape(50, Color::Yellow(),true);
    engine.world.emplace<ColliderComponent>(f,circle3, true, 1000000);
    engine.world.emplace<NameGroupComponent>(f,"enemy2 ", "enemies");

    while(engine.NextFrame()){

        engine.Update();

        engine.Render();
    }


    return 0;
}