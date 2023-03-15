#include "Nexus.hh"

int main(int argc, char *args[]){

    int width = 800;
    int height = 800;
    Nexus engine = Nexus (width,height);

    const auto ball = engine.world.create();

    engine.world.emplace<TransformComponent>(ball, Vec2(0.0,height/4));
    
    engine.world.emplace<KinematicComponent>(ball, Vec2(100, -200), Vec2 (0,100));
    //engine.world.emplace<KinematicComponent>(ball, Vec2(50, 100), Vec2 (0,100)); // Yvel = 0 --> the ball keeps on the floor
    //engine.world.emplace<KinematicComponent>(ball, Vec2(50, -100), Vec2 (0,100));
    //engine.world.emplace<KinematicComponent>(ball, Vec2(200, -300), Vec2 (0,100)); // reaches the top boundary
    //engine.world.emplace<KinematicComponent>(ball, Vec2(150, -80), Vec2 (0,100));
    //engine.world.emplace<KinematicComponent>(ball, Vec2(80, -50), Vec2 (0,100));
    //engine.world.emplace<KinematicComponent>(ball, Vec2(-80, -50), Vec2 (0,100)); // doesnt apper --> it goes to the left

    while (engine.NextFrame()){
        engine.Update();

        // Check world boundaries
        auto transform = engine.world.get<TransformComponent>(ball);
        if(transform.position.y > 3*height/4 - 100)
        transform.position.y = 3*height/4 - 100;

        if(transform.position.x > width)
        transform.position.x = width;

        Color color_sky_blue= Color::color(179,237,252);
        Color color_grass_green = Color::color(11,99,23);

        //Render ball and background
        engine.DrawFillRect(width/2, height/4,width,height-200, color_sky_blue);
        engine.DrawFillRect(width/2,height*0.75+100 ,width,2*height/4, color_grass_green);
        //engine.DrawFillRect(width/2,height/4,width,height/2, Color::Blue());
        //engine.DrawFillRect(width/2,height * 0.75,width,height/2, Color::Green());
        engine.DrawFillCircle(transform.position.x, transform.position.y, 20, Color::color(0, 0, 204));
        
        engine.Render();
        }

    return 0;
}