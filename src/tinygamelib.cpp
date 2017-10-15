#include "tinygamelib.h"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

TinyGameLibrary::TinyGameLibrary(const string& name, int width, int height, int gridSize, int scale)
{
    m_renderWidth = width;
    m_renderHeight = height;
    m_gridSize = gridSize;

    width *= scale;
    height *= scale;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cerr << "Unable to initialize SDL: " << SDL_GetError() << endl;
        exit(1);
    }

    if (SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_OPENGL, &m_window, &m_renderer)) {
        cerr << "Unable to create SDL window or renderer: " << SDL_GetError() << endl;
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 1024)) {
        cerr << "Unable to initialize SDL audio: " << SDL_GetError() << endl;
        exit(1);
    }

    SDL_SetWindowTitle(m_window, name.c_str());
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderSetScale(m_renderer, (float)scale, (float)scale);

    m_spritesheet = nullptr;
}

TinyGameLibrary::~TinyGameLibrary()
{    
    if (m_spritesheet != nullptr) SDL_DestroyTexture(m_spritesheet);

    Mix_CloseAudio();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void TinyGameLibrary::mainLoop()
{
    m_run = true;

    while (m_run) {
        SDL_RenderClear(m_renderer);
        readKeys();
        render();
        SDL_Delay(1000 / 30);
    }
}

void TinyGameLibrary::readKeys()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    m_run = false;
                    break;
                case SDLK_LEFT:
                    m_objects.at(m_playerIdx).x--;
                    break;
                case SDLK_RIGHT:
                    m_objects.at(m_playerIdx).x++;
                    break;
                case SDLK_UP:
                    m_objects.at(m_playerIdx).y--;
                    break;
                case SDLK_DOWN:
                    m_objects.at(m_playerIdx).y++;
                    break;
            }
        }
    }
}

void TinyGameLibrary::render()
{
    TGL_Level& level = m_levels.at(0);

    for (int i = 0; i < level.h; i++) {
        for (int j = 0; j < level.w; j++) {
            int mapIdx = j + i * level.h;
            vector<int> layers = level.map.at(mapIdx);
            for (unsigned int k = 0; k < layers.size(); k++) {
                TGL_Object obj;
                obj.x = j * m_gridSize;
                obj.y = i * m_gridSize;
                obj.objectTypeId = layers.at(k);
                renderSprite(obj);
            }
        }
    }

    for (auto& obj : m_objects) {
        renderSprite(obj);
    }

    SDL_RenderPresent(m_renderer);
}

void TinyGameLibrary::renderSprite(const TGL_Object& object)
{
    TGL_SpriteCoord spriteCoord = m_objectTypes.at(object.objectTypeId).spriteCoords.at(object.direction);
    SDL_Rect srcRect = { spriteCoord.x, spriteCoord.y, spriteCoord.w, spriteCoord.h };
    SDL_Rect dstRect = { object.x, object.y, srcRect.w, srcRect.h };
    SDL_RenderCopy(m_renderer, m_spritesheet, &srcRect, &dstRect);

}

void TinyGameLibrary::setSpritesheet(const string& spritesheet)
{
    SDL_Surface* temp = IMG_Load(spritesheet.c_str());
    if (temp == nullptr) {
        cerr << "Unable to load spritesheet: " << spritesheet << endl;
        return;
    }

    SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, 255, 0, 255));

    SDL_DestroyTexture(m_spritesheet);
    m_spritesheet = SDL_CreateTextureFromSurface(m_renderer, temp);
    SDL_FreeSurface(temp);
}

void TinyGameLibrary::addObject(TGL_Id id, const string& name, TGL_Type type, vector<TGL_Direction, TGL_SpriteCoord> spriteCoord)
{
    TGL_ObjectType objectType;
    objectType.name = name;
    objectType.type = type;
    objectType.spriteCoord = spriteCoord;
    m_objectTypes[id] = objectType;
}

void TinyGameLibrary::addLevel(const string& name, int width, int height, const vector<vector<TGL_Id>>& map)
{
    TGL_Level level;
    level.name = name;
    level.w = width;
    level.h = height;
    level.map = map;

    m_playerIdx = -1;
    for (unsigned int i = 0; i < level.map.size(); i++) {
        for (unsigned int j = 0; j < level.map.at(i).size(); j++) {
            TGL_Id objTypeId = level.map.at(i).at(j);
            TGL_ObjectType objtype = m_objectTypes.at(objTypeId);
            if (objtype.type == TGL_Type::Player || objtype.type == TGL_Type::Enemy) {
                int x = (i % level.w) * m_gridSize;
                int y = (i / level.w) * m_gridSize;
                TGL_Object object = { x, y, TGL_Direction::Down, TGL_State::Stopped, objTypeId };
                m_objects.push_back(object);

                if (objtype.type == TGL_Type::Player) m_playerIdx = m_objects.size() - 1;

                auto& v = level.map.at(i);
                v.erase(v.begin() + (signed)j);
            }
        }
    }

    m_levels.push_back(level);
}
