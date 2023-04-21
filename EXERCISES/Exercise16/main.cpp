#include "Nexus.hh"
#include <iostream>

int main(int argc, char* argv[]){

    sol::state lua;
    lua.open_libraries(sol::lib::base);
    lua.script_file("./../assets/scripts/exercise16.lua");

    sol::table config = lua["config"];
    int width = config["resolution"]["width"];
    int height = config["resolution"]["height"];
    int totalParticles = config["totalparticles"];
    int particleRadius = config["particle"]["radius"] ;
    Color color1 = Color::color(config["particle"]["color1"]["r"],config["particle"]["color1"]["g"],config["particle"]["color1"]["b"]);
    Color color2 = Color::color(config["particle"]["color2"]["r"],config["particle"]["color2"]["g"],config["particle"]["color2"]["b"]);


    Nexus engine = Nexus(width,height);
    vector<entt::entity> particles;


    for (int i=0; i<totalParticles; i++)
    {
        const auto ball = engine.world.create();
        // we create a new ball on each iteration (entity)
        Vec2 position = Vec2::FromModuleAngle(300, (2*M_PI/totalParticles)*(i));
        // the angle keeps changing in each iteration
        engine.world.emplace<TransformComponent>(ball,position + Vec2(400,400)); // if we dont pass an argument --> default values
        particles.push_back(ball);
    }


    while(engine.NextFrame()){

        engine.Update();

        for(auto& ball: particles)
        {
            //show all the entities created on the screen
            auto i = &ball - &particles[0];
            auto& transform =engine.world.get<TransformComponent>(ball);
            Color color = Color::Lerp(
                color1,
                color2,
                (float)i/(float)totalParticles); //calcula un valor entre 0 y 1 que representa la posición de la partícula actual en un conjunto de partículas
            
            Graphics::DrawFillCircle(transform.position.x, transform.position.y, particleRadius, color);
        }
    engine.Render();

    }

    
    return 0;
}