#include "Nexus.hh"

int main(int argc, char *argv[]){

    Nexus engine = Nexus(800,800);

    for (int i = 1; i<5;i++){
        const auto car = engine.world.create();
        engine.world.emplace<TransformComponent>(car, Vec2(50.0,50+50*i));
        engine.world.emplace<KinematicComponent>(car,Vec2(90,0));
        engine.world.emplace<NameGroupComponent>(car,"car " + std::to_string(i), "cars");
    }

    for (int i = 1; i<5;i++){
        const auto frog = engine.world.create();
        engine.world.emplace<TransformComponent>(frog, Vec2(400,500+50*i));
        engine.world.emplace<KinematicComponent>(frog,Vec2(0,-80));
        engine.world.emplace<NameGroupComponent>(frog,"frog " + std::to_string(i), "frogs");
    }

    while(engine.NextFrame()){
        engine.Update();

        float dt = engine.GetDeltaTime();
        std::cout << dt << std::endl;
        //float totalTime = engine.GetTotalTimeInMilliSeconds();

        auto view = engine.world.view<NameGroupComponent,TransformComponent>();
        for (auto entity : view){
            const auto nameGroup = view.get<NameGroupComponent>(entity);
            auto& transform = view.get<TransformComponent>(entity);

            if (nameGroup.group == "cars"){
                //transform.position += Vec2(400,0) * dt;
                Graphics::DrawFillRect(transform.position.x, transform.position.y, 40,30, Color::Red());
                if (transform.position.x - 20 >= engine.width)
                    transform.position.x  = - 20;
                
            }

            if (nameGroup.group == "frogs"){
                //transform.position += Vec2(0,-400) * dt;
                Graphics::DrawFillCircle(transform.position.x, transform.position.y, 20, Color::Green());
                if (transform.position.y + 10 <= 0)
                    transform.position.y  = engine.height+10;
            }
        }

        engine.Render();
    }

    return 0;
}