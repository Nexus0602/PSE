#include "Nexus.hh"
using namespace std;

int main(int argc,char *args[])
{
    int width = 800;
    int height = 800;
    Nexus engine = Nexus (width,height);
    Vec2 anchor = Vec2(width/2,60);
    float k=150;
    float restLength = 200;

    vector<entt::entity> bobs;
    vector<Vec2>anchors;
    int totalBobs = 3;
    float pos_y =anchor.y + restLength + 100;

    for (int i=0; i<totalBobs; i++){
        anchors.push_back(anchor);
        const auto bob = engine.world.create();
        engine.world.emplace<TransformComponent>(bob, Vec2(width/2, pos_y));
        engine.world.emplace<KinematicComponent>(bob);
        engine.world.emplace<ParticleComponent>(bob,1,10);
        engine.world.emplace<DragAndDropImpulseComponent>(bob,0.05);
        bobs.push_back(bob);
        const auto t = engine.world.get<TransformComponent>(bob);
        anchor = t.position;
        pos_y = anchor.y + restLength + 100;

    }

    while(engine.NextFrame())
    {
        engine.Update();

        int index = 0;
        Vec2 prev_springForce = Vec2(0,0);
        anchor = anchors[index];
        for(auto& bob: bobs){

            const auto t = engine.world.get<TransformComponent>(bob);
            const auto kinematic = engine.world.get<KinematicComponent>(bob);
            auto& p = engine.world.get<ParticleComponent>(bob);
            Vec2 dragForce = Force::GenerateDragVector(0.1,kinematic.velocity);
            p.AddForce(dragForce);
            Vec2 weightForce = Vec2(0,20);
            p.AddForce(weightForce);
            Vec2 springForce = Force::GenerateSpringVector(t.position, anchor, restLength,k);
            p.AddForce(springForce);
            p.AddForce(prev_springForce);

            Graphics::DrawLine(t.position.x,t.position.y, anchor.x, anchor.y, Color::White());
            if (index == 0)
                Graphics::DrawFillRect(anchor.x,anchor.y,30,10,Color::Red());
            index ++;
            prev_springForce = springForce;
            anchor = t.position;
        }
        engine.Render();
    }
    return 0;
}


    
