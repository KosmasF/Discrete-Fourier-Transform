#ifndef GRAPH_H
#define GRAPH_H

#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include "Exceptions.h"
#include "Map.h"

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

#endif