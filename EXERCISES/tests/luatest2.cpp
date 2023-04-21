#include "Nexus.hh"


int main (int argc, char *args[]){

    Nexus engine = Nexus(800,800);
    engine.lua.script_file("./../assets/scripts/scripts-component-01.lua");
    setup_scene(engine);


    return 0;
}