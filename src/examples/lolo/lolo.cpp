#include "lolo.h"

#include <vector>

Lolo::Lolo()
{
    TinyGameLibrary tgl("Lolo", 320, 200, 16, 4);

    tgl.setSpritesheet("data/spritesheet.png");
    tgl.addObject(0, "Brick", TGL_Type::Floor, { 0, 0, 16, 16 });
    tgl.addObject(1, "Rock", TGL_Type::Block, { 16, 0, 16, 16 });
    tgl.addObject(2, "Tree", TGL_Type::Block, { 32, 0, 16, 16 });
    tgl.addObject(3, "Heart", TGL_Type::Block, { 48, 0, 16, 16 });
    tgl.addObject(4, "Chest", TGL_Type::Block, { 64, 0, 16, 16 });
    tgl.addObject(5, "Lolo", TGL_Type::Player, {
        { TGL_Direction::Left,{ 0, 16, 16, 16, 8 } },
        { TGL_Direction::Right,{ 0, 16, 16, 16, 8 } },
        { TGL_Direction::Up,{ 0, 16, 16, 16, 8 } },
        { TGL_Direction::Down,{ 0, 16, 16, 16, 8 } }
    });
    tgl.addObject(6, "Snake", TGL_Type::Enemy, { 0, 32, 16, 16 });
    
    vector<vector<TGL_Id>> map = {
        { 0, 1 },{ 0, 1 },{ 0, 1 },{ 0, 1 },{ 0, 1 },{ 0, 1 },{ 0    },{ 0, 1 },{ 0, 1 },{ 0, 2 },{ 0, 2 },
        { 0, 1 },{ 0, 2 },{ 0, 2 },{ 0, 1 },{ 0, 3 },{ 0    },{ 0    },{ 0, 1 },{ 0, 1 },{ 0, 2 },{ 0, 2 },
        { 0    },{ 0, 2 },{ 0, 2 },{ 0, 1 },{ 0, 1 },{ 0, 1 },{ 0    },{ 0, 1 },{ 0, 1 },{ 0, 1 },{ 0, 2 },
        { 0    },{ 0    },{ 0, 2 },{ 0, 2 },{ 0, 1 },{ 0, 1 },{ 0    },{ 0, 1 },{ 0, 1 },{ 0, 1 },{ 0, 2 },
        { 0, 5 },{ 0    },{ 0    },{ 0    },{ 0, 1 },{ 0, 1 },{ 0    },{ 0, 1 },{ 0, 1 },{ 0, 2 },{ 0, 3 },
        { 0    },{ 0    },{ 0    },{ 0    },{ 0    },{ 0    },{ 0, 6 },{ 0    },{ 0, 1 },{ 0    },{ 0    },
        { 0    },{ 0, 2 },{ 0, 2 },{ 0    },{ 0    },{ 0    },{ 0    },{ 0    },{ 0    },{ 0    },{ 0    },
        { 0, 2 },{ 0, 2 },{ 0, 2 },{ 0, 2 },{ 0    },{ 0    },{ 0    },{ 0, 2 },{ 0, 2 },{ 0    },{ 0    },
        { 0, 2 },{ 0, 2 },{ 0, 2 },{ 0, 2 },{ 0    },{ 0    },{ 0    },{ 0, 2 },{ 0, 2 },{ 0, 2 },{ 0    },
        { 0, 1 },{ 0, 2 },{ 0, 2 },{ 0, 1 },{ 0, 4 },{ 0    },{ 0    },{ 0    },{ 0, 2 },{ 0, 2 },{ 0    },
        { 0, 1 },{ 0, 1 },{ 0, 1 },{ 0, 1 },{ 0, 1 },{ 0, 1 },{ 0    },{ 0    },{ 0    },{ 0    },{ 0    }
    };
    tgl.addLevel("Level 1", 11, 11, map);

    tgl.mainLoop();
}

int main()
{
    Lolo();
}
