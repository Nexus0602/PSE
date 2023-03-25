#include "Nexus.hh"

int main(int argc,char *args[])
{
    int width = 800;
    int height = 800;
    Nexus engine = Nexus (width,height);

    Vec2 gravityForce = Vec2(0,50);
    Vec2 dragForce = Vec2();

    const auto particle = engine.world.create();
    engine.world.emplace<TransformComponent>(particle, Vec2(width/2,50.0));
    engine.world.emplace<KinematicComponent>(particle ,Vec2(0,0), Vec2(0,0));
    engine.world.emplace<ParticleComponent>(particle,1,20,Color::Red());

    auto& t = engine.world.get<TransformComponent>(particle);
    auto& k = engine.world.get<KinematicComponent>(particle);
    auto& p = engine.world.get<ParticleComponent>(particle);

    while(engine.NextFrame())
    {
        engine.Update();

        p.AddForce(gravityForce);

        //we only enable the drag force when the particle is in the liquid
        if(t.position.y >=height/2)
        {
            dragForce = Force::GenerateDragVector( 0.1 ,k.velocity);
        }
        else
        {
            dragForce=Vec2();
        }
        p.AddForce(dragForce);

        std::cout << "Velocity: " << k.velocity << "\tDrag force: " << dragForce << std::endl;

        Graphics::DrawFillRect(width/2, height *0.75, width, height/2, Color::color(14,91,158));
        engine.Render();
    }
    return 0;
}


    
