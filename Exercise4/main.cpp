#include "Nexus.hh"

int last_frame_time=0;

int main(int argc, char *args[]){

    //Initialize game engine
//Nexus engine(640,400);
//engine.Start(); // juntar con constructor ???
    Nexus engine = Nexus(640,400);

    //Define the player
    struct {
        float x = 20;
        float y= 20;
        float widht = 10;
        float height = 10;
        float speed_x = 40;
        float speed_y = 40;
    } player;

    // Game loop
    while(engine.NextFrame()){
        engine.Update();

        double dt = engine.GetDeltaTime(&last_frame_time);

        if (player.x > 640 - player.widht/2 || player.x < player.widht/2) {
        player.speed_x = -player.speed_x;
        }
        if (player.y > 400 - player.height/2 || player.y < player.height/2) {
            player.speed_y = -player.speed_y;
        }
        player.x += player.speed_x * dt;
        player.y += player.speed_y * dt;

        engine.DrawRect(
            player.x,
            player.y,
            player.widht,
            player.height,
            Color::Yellow()
        );
        //engine.DrawCircle(player.x,player.y, player.widht, Color::Yellow(),atan(1));
        Logger::Info("Player position: " + std::to_string(player.x) + ", " + std::to_string(player.y));

        engine.Render();
    }

    engine.~Nexus();

    return 0;

}