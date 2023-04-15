#include "Nexus.hh"
#include <iostream>

using namespace std;

void OnKeyDown(const KeyDownEvent& keyDown) noexcept {
    cout << "KeyDown event " << keyDown.symbol << endl;
    if (keyDown.symbol == SDLK_UP){
        cout << "pressed UP arrow " << endl;
    }
}

int main(int argc, char *argv[]){

    Nexus engine = Nexus(800,800);

    engine.eventBus.sink<KeyDownEvent>().connect<&OnKeyDown>();

    while(engine.NextFrame()){
        engine.Update();
        engine.Render();
    }

    return 0;
}