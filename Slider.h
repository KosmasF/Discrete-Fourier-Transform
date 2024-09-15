#ifndef SLIDER_H
#define SLIDER_H

#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>
#include "Exceptions.h"
#include "Map.h"
#include "Circle.h"


#define DEFAULT_SLIDER_HEIGHT 50
#define X_OFFSET 5
#define BALL_RADIUS 5

struct SliderWindow
{
    int numSliders;
    struct Slider* sliders;
    struct SDL_Window* window;
    int width;
    int height;
    TTF_Font* font;
};

struct Slider
{
    const char* name;
    float start;
    float end;
    float* variable;
};


void SliderWindowSetup(struct SliderWindow* sliderWindow, const char* name, int numSliders, int width);
void SliderWindowHandleEvent(struct SliderWindow* sliderWindow, Uint32 event);
void SliderWindowClose(struct SliderWindow* sliderWindow);
void SliderWindowDraw(struct SliderWindow* sliderWindow);

void SliderSetup(struct SliderWindow* sliderWindow, int id, float minValue, float maxValue, const char* name, float* variable);



#endif