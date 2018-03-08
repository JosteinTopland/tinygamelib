#include "vampire.h"

Vampire::Vampire()
{
    TinyGameLibrary tgl("Vampire", 320, 200, 1);
    tgl.setSpritesheet("src/examples/vampire/data/sprites.png");
    tgl.addObject(0, "hero", TGL_Type::Player, {{TGL_Direction::Down, {0, 0, 16, 16, 1}}});
    tgl.addLevel("level 1", 1, 1, {
        { 0 }
    });
    tgl.mainLoop();
}

int main()
{
    Vampire();
}