#ifndef GRAPH_H
#define GRAPH_H

#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>

extern void *__cxa_allocate_exception(size_t thrown_size);
extern void __cxa_throw (void *thrown_exception, void* *tinfo, void (*dest) (void *) );
extern void * _ZTIl; // typeinfo of long

struct GraphWindow
{
	SDL_Window* window;
	int screenWidth;
	int screenHeight;
	int windowWidth;
	int windowHeight;
};

struct Graph
{
	int maxNum;
	int numValues;
	float* data;
	struct GraphWindow window;
};

void graphSetupWindow(struct Graph* this, const char* name, int width, int height);
void graphSetMaxValues(struct Graph* this, int maxValues);
void graphDestroy(struct Graph* this);
void graphDestroyWindow(struct Graph* this);
void graphAddValue(struct Graph* this, float value);
void graphDraw(struct Graph* this);

float graphGetMaxValue(struct Graph* this);
float graphGetMinValue(struct Graph* this);
float graphGetAverage(struct Graph* this, int start, int end);

float map(float value, float min, float max, float mapMin, float mapMax);

#endif