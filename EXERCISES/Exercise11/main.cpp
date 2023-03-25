#include "Nexus.hh"
int main(int argc,char *args[]){

    int width=800;
    int height=800;
    Nexus engine= Nexus(width,height);
    int torque = 500;

    const auto circle=engine.world.create();
    engine.world.emplace<TransformComponent>(circle, Vec2(200,200));
    engine.world.emplace<KinematicComponent>(circle);
    CircleShape c1 =CircleShape(100,Color::Red(),false);
    engine.world.emplace<RigidBodyComponent>(circle,1,c1);

    const auto circleFilled=engine.world.create();
    engine.world.emplace<TransformComponent>(circleFilled, Vec2(600,200));
    engine.world.emplace<KinematicComponent>(circleFilled);
    CircleShape c2 = CircleShape(100,Color::Green(),true);
    engine.world.emplace<RigidBodyComponent>(circleFilled,1,c2);

    RectangleShape r1 = RectangleShape(200,100,Color::Yellow(),false);
    const auto rectangle=engine.world.create();
    engine.world.emplace<TransformComponent>(rectangle, Vec2(200,600));
    engine.world.emplace<KinematicComponent>(rectangle);
    engine.world.emplace<RigidBodyComponent>(rectangle,1,r1);
    
    const auto rectangleFilled=engine.world.create();
    engine.world.emplace<TransformComponent>(rectangleFilled, Vec2(600,600));
    engine.world.emplace<KinematicComponent>(rectangleFilled);
    RectangleShape r2 = RectangleShape(200,100,Color::White(),true);
    engine.world.emplace<RigidBodyComponent>(rectangleFilled,1,r2);

    while(engine.NextFrame()){

        engine.Update();

        auto& circleRb=engine.world.get<RigidBodyComponent>(circle);
        auto& circlek = engine.world.get<KinematicComponent>(circle);
        
        auto& rectanglek=engine.world.get<KinematicComponent>(rectangle);
        auto& rectangleRb=engine.world.get<RigidBodyComponent>(rectangle);
    
        if (engine.keyboard->downKeyPressed){
            rectangleRb.AddTorque(-torque);
            
        }
        if (engine.keyboard->upKeyPressed){
            circleRb.AddTorque(torque);
        }

        std::cout <<"Rectangle Angular velocity:"<<engine.world.get<KinematicComponent>(rectangle).angularVelocity 
                    <<"\tCircle Angular velocity: "<<engine.world.get<KinematicComponent>(circle).angularVelocity
                    << std::endl
                    //<< "\t Circle Acceleration: " <<circlek.angularAcceleration// <<
                    //"\tFilledCircle Angular velocity:"<<engine.world.get<KinematicComponent>(circleFilled).angularVelocity
                    << std::endl;
        engine.Render();
    }
    return 0;

}