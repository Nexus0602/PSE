#include "Nexus.hh"
//#include <vector>
using namespace std;

int main(int argc, char *argv[])
{

vector<entt::entity> particles;

int totalParticles = 20;
int particleRadius = 20;

if (argc == 3)
{
    totalParticles = strtol(argv[1], nullptr,0);
    particleRadius = strtol (argv[2],nullptr,0);
}

Nexus engine = Nexus(800,800); 

for (int i=0; i<totalParticles; i++)
{
    const auto ball = engine.world.create();
    Vec2 position = Vec2::FromModuleAngle(300, (2*M_PI/totalParticles)*(i));
    engine.world.emplace<TransformComponent>(ball,position + Vec2(400,400));
    particles.push_back(ball);
}

while(engine.NextFrame())
{
    engine.Update();

    for(auto& ball: particles)
    {
        auto i = &ball - &particles[0];
        auto& transform =engine.world.get<TransformComponent>(ball);
        Color color = Color::Lerp(
            Color::Blue(),
            Color::Yellow(),
            (float)i/(float)totalParticles);
        
        Graphics::DrawFillCircle(transform.position.x, transform.position.y, particleRadius, color);
    }
    engine.Render();
}

return 0;

}
