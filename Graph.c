#include "Graph.h"

void graphSetMaxValues(struct Graph* this, int maxValues)
{
	//Raylib::InitWindow(1920 / 2, 1080 / 2, "Graph");

	this->maxNum = maxValues;
	this->data = malloc(maxValues * sizeof(float));
	this->numValues = 0;
}

void graphSetupWindow(struct Graph* this, const char* name, int width, int height)
{
	int ret;

	SDL_DisplayMode DM;
	ret = SDL_GetDesktopDisplayMode(0, &DM);
	if( ret != 0 ){
		SDL_Log("SDL_GetDesktopDisplayMode failed: %s\n", SDL_GetError());
		int64_t * p = (int64_t*)__cxa_allocate_exception(8);
		__cxa_throw(p, &_ZTIl, 0);
	}
	const int ScreenWidth = DM.w;
	const int ScreenHeight = DM.h;

	SDL_Window* win = SDL_CreateWindow( name, (ScreenWidth / 2) - (width / 2), (ScreenHeight / 2) - (height / 2), width, height, SDL_WINDOW_SHOWN );

	if ( win == NULL ) {
		SDL_Log("Failed to create a window! Error: %s\n", SDL_GetError());
		int64_t * p = (int64_t*)__cxa_allocate_exception(8);
		__cxa_throw(p, &_ZTIl, 0);
	}

	SDL_Renderer* renderer = SDL_CreateRenderer( win, -1, SDL_RENDERER_ACCELERATED );

	this->window = (struct GraphWindow){win, ScreenWidth, ScreenHeight, width, height};
}

void graphDraw(struct Graph* this)
{
	SDL_Renderer* winRenderer = SDL_GetRenderer(this->window.window);

	SDL_SetRenderDrawColor(winRenderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear( winRenderer );

	float max = graphGetMaxValue(this);
	float min = graphGetMinValue(this);

	float x = this->window.windowWidth / ((float)(this->numValues) - 1);

	SDL_SetRenderDrawColor(winRenderer, 0xff, 0x00, 0x00, 0xff);
	for (int i = 0; i < this->numValues - 1; i++)
	{
		int y1 = (int)map(this->data[i], min, max, this->window.windowHeight, 0);
		int y2 = (int)map(this->data[i + 1], min, max, this->window.windowHeight, 0);
		SDL_RenderDrawLine(winRenderer, x * i, y1, x * (i+1), y2);
	}

	float averageStart = graphGetAverage(this, 0, this->numValues / 2);
	float averageEnd = graphGetAverage(this, this->numValues / 2, this->numValues);

	SDL_SetRenderDrawColor(winRenderer, 0x00, 0xff, 0x00, 0xff);
	SDL_RenderDrawLine(winRenderer, 0, map(averageStart, min, max, this->window.screenHeight, 0), this->window.screenWidth, map(averageEnd, min, max, this->window.screenHeight, 0));


	SDL_RenderPresent( winRenderer);
	SDL_UpdateWindowSurface(this->window.window);
}

void graphAddValue(struct Graph* this, float value)
{
	if (this->numValues == this->maxNum)
	{
		for(int i = 0; i < this->maxNum - 1; i++)
		{
			this->data[i] = this->data[i + 1];
		}

		this->data[this->numValues - 1] = value;
	}
	else {

		this->data[this->numValues] = value;
		this->numValues++;
	}
}

void graphDestroyWindow(struct Graph* this)
{
	SDL_DestroyRenderer(SDL_GetRenderer(this->window.window));
	SDL_DestroyWindow(this->window.window);
}

float graphGetMaxValue(struct Graph* this)
{
	float result = 0;
	for (int i = 0; i < this->numValues; i++)
		if (this->data[i] > result)
			result = this->data[i];
	return result;
}

float graphGetMinValue(struct Graph* this)
{
	float result = ((float)(1e+300 * 1e+300));//INF
	for (int i = 0; i < this->numValues; i++)
		if (this->data[i] < result)
			result = this->data[i];
	return result;
}

float graphGetAverage(struct Graph* this, int start, int end)
{
	int num = end - start;
	float result = 0;
	for (int i = start; i < end; i++)
		result += this->data[i];
	return result / num;
}

void graphDestroy(struct Graph* this)
{
	free(this->data);
	this->maxNum = 0;
	this->numValues = 0;
}