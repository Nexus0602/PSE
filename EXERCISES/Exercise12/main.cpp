#include "Nexus.hh"

int main(int argc, char *argv[]){

    Nexus engine = Nexus(800,800);

    while(engine.NextFrame()){
        engine.Update();

        Graphics::DrawGrid(100);
        engine.Render();
    }

    return 0;
}