#include "Nexus.hh"

using namespace std;

float constant_speed = 2.5;
float enemy_vision_angle = 90;

int main(int argc, char** argv){

    struct object {
    Vec2 position;
    int width;
    int height;
    Color color;
    } player, enemy;

    Nexus engine = Nexus(640,400);

    //Entities initialization

    player.width = 10;
    player.height = 10;
    player.position = Vec2(100,100);
    player.color = Color::Blue();

    enemy.width = 10;
    enemy.height = 10;
    enemy.position = Vec2(200,200);
    enemy.color = Color::Red();

    while (engine.NextFrame()){
        engine.Update();
        Vec2 mouse_pos = engine.CheckMousePos();

        // actualizar player.position en funcion del mouse
        player.position = mouse_pos;

        Vec2 direction = player.position - enemy.position;
        Vec2 normal_direction = direction.UnitVec();
        Vec2 normal_enemy = enemy.position.UnitVec();

        float dot = (normal_direction.Magnitude() * normal_enemy.Magnitude() * cos(enemy_vision_angle/2));
        
        cout << dot << endl;
        cout << normal_direction.Dot(normal_enemy) << endl;

        if (normal_direction.Dot(normal_enemy) >= dot) {
            enemy.position += normal_direction * constant_speed;

        }

        engine.DrawFillRect(
            player.position.x,
            player.position.y,
            player.width,
            player.height,
            player.color
        );

        engine.DrawFillRect(
            enemy.position.x,
            enemy.position.y,
            enemy.width,
            enemy.height,
            enemy.color
        );
        
        Logger::Info("Player position: " + std::to_string(player.position.x) + ", " + std::to_string(player.position.y));
        Logger::Info("Enemy position: " + std::to_string(enemy.position.x) + ", " + std::to_string(enemy.position.y));
        engine.Render();
    }

    engine.~Nexus();

    return 0;
}