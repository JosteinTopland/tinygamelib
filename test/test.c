#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

SDL_Window* window;
SDL_Renderer* renderer;
char run = 1;

typedef struct {
    int x, y;
    int w, h;
    SDL_Texture* texture;
} TGL_Sprite;

void TGL_Init(int width, int height, int scale) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(scale * width, scale * height, SDL_WINDOW_OPENGL, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderSetScale(renderer, scale, scale);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 1024);
}

void TGL_Deinit() {
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

TGL_Sprite TGL_LoadSprite(const char* file, int x, int y) {
    TGL_Sprite sprite;
    sprite.x = x;
    sprite.y = y;

    SDL_Surface* image = SDL_LoadBMP(file);
    sprite.w = image->w;
    sprite.h = image->h;
    sprite.texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    return sprite;
}

void TGL_ReadEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            run = 0;
        }
    }
}

void TGL_RenderSprite(TGL_Sprite* sprite) {
    SDL_Rect rect = { sprite->x, sprite->y, sprite->w, sprite->h };
    SDL_RenderCopy(renderer, sprite->texture, NULL, &rect);
}

// ----------------------------------------------------------------------------

int main(int argc, char* argv[]) {
    char fps = 10;
 
    TGL_Init(320, 200, 4);
    TGL_Sprite sprite1 = TGL_LoadSprite("leanne.bmp", 0, 0);
    TGL_Sprite sprite2 = TGL_LoadSprite("leanne2.bmp", 100, 0);
    Mix_Music* music = Mix_LoadMUS("ACIDJAZ1.MOD");
    //Mix_PlayMusic(music, 1);

    while (run) {
        TGL_ReadEvents();
        SDL_SetRenderDrawColor(renderer, rand() % 256, rand() % 256, rand() % 256, 255);
        SDL_RenderClear(renderer);
        TGL_RenderSprite(&sprite1);
        TGL_RenderSprite(&sprite2);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / fps);
    }

    TGL_Deinit();
    return 0;
}
