#ifndef TINYGAMELIB_H
#define TINYGAMELIB_H

#include <map>
#include <string>
#include <vector>

using namespace std;

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

enum class TGL_Type {
    Floor,
    Block,
    Player,
    Enemy
};

enum class TGL_Direction {
    Left,
    Right,
    Up,
    Down
};

enum class TGL_State {
    Stopped,
    Walking
};

typedef int TGL_Id;

typedef struct {
    int x, y, w, h, frames;
} TGL_SpriteCoord;

class TinyGameLibrary
{
public:
    TinyGameLibrary(const string& name, int width, int height, int gridSize, int scale = 1);
    ~TinyGameLibrary();
    void mainLoop();
    void setSpritesheet(const string& spritesheet);
    void addObject(TGL_Id id, const string& name, TGL_Type type, map<TGL_Direction, TGL_SpriteCoord> spriteCoords);
    void addLevel(const string& name, int width, int height, const vector<vector<TGL_Id>>& map);

private:    
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_spritesheet;
    
    bool m_run;
    int m_renderWidth;
    int m_renderHeight;
    int m_gridSize;

    typedef struct {
        int x, y;
        TGL_Direction direction;
        TGL_State state;
        TGL_Id objectTypeId;
    } TGL_Object;
    vector<TGL_Object> m_objects;

    typedef struct {
        string name;
        TGL_Type type;
        map<TGL_Direction, TGL_SpriteCoord> spriteCoords;
    } TGL_ObjectType;
    map<TGL_Id, TGL_ObjectType> m_objectTypes;

    typedef struct {
        string name;
        int w, h;
        vector<vector<TGL_Id>> map;
    } TGL_Level;
    vector<TGL_Level> m_levels;

    TGL_Id m_playerIdx;

    void readKeys();
    void render();
    void renderSprite(const TGL_Object& object);
};

#endif
