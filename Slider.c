#include "Slider.h"

void SliderWindowSetup(struct SliderWindow* sliderWindow, const char* name, int numSliders, int width)
{
    int ret;

	SDL_DisplayMode DM;
	const int ScreenWidth = DM.w;
	const int ScreenHeight = DM.h;
    const int height = numSliders * DEFAULT_SLIDER_HEIGHT;

	SDL_Window* win = SDL_CreateWindow( name, (ScreenWidth / 2) - (width / 2), (ScreenHeight / 2) - (height / 2), width, height, SDL_WINDOW_SHOWN );

	SDL_Renderer* renderer = SDL_CreateRenderer( win, -1, SDL_RENDERER_ACCELERATED );

    TTF_Init();

    TTF_Font* font;

    font = TTF_OpenFont("LiberationMono-Regular.ttf", 24);
    if ( !font ) {
        printf("Failed to load font: %s\n", TTF_GetError());
    }

    struct Slider* sliders = malloc(numSliders * sizeof(struct Slider));

	*sliderWindow = (struct SliderWindow){numSliders, sliders, win, width, height, font};
}

void SliderWindowClose(struct SliderWindow* sliderWindow)
{
	SDL_DestroyRenderer(SDL_GetRenderer(sliderWindow->window));
	SDL_DestroyWindow(sliderWindow->window);
    free(sliderWindow->sliders);
}

void SliderWindowHandleEvent(struct SliderWindow* sliderWindow, Uint32 event)
{
}

void SliderSetup(struct SliderWindow *sliderWindow, int id, float minValue, float maxValue,const char* name, float *variable)
{
    sliderWindow->sliders[id] = (struct Slider){name ,minValue, maxValue, variable};
}

void SliderWindowDraw(struct SliderWindow* sliderWindow)
{
    SDL_Renderer* renderer = SDL_GetRenderer(sliderWindow->window);

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear( renderer );

    int heightBuffer = 0;
    for(int i = 0; i < sliderWindow->numSliders; i++)
    {
        struct Slider* currentSlider = &(sliderWindow->sliders[i]);

        //Text
        SDL_Surface* text;
        SDL_Color color = { 0x00, 0x00, 0x00 };

        text = TTF_RenderText_Solid( sliderWindow->font, currentSlider->name, color );
        if ( !text ) {
            printf("Failed to render text: %s\n", TTF_GetError());
        }

        SDL_Texture* text_texture;
        text_texture = SDL_CreateTextureFromSurface( renderer, text );
        SDL_Rect dest = { 0, heightBuffer, text->w, text->h };
        SDL_RenderCopy( renderer, text_texture, NULL, &dest );

        //Line
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
        SDL_RenderDrawLine(renderer, X_OFFSET, heightBuffer + 30, sliderWindow->width - X_OFFSET, heightBuffer + 30);

        //Circle
        SDL_Point point = (SDL_Point){
            map(*(currentSlider->variable), currentSlider->start, currentSlider->end, 0 + X_OFFSET, sliderWindow->width - X_OFFSET),
            heightBuffer + 30
            };
        DrawCircle(renderer, point, BALL_RADIUS);

        heightBuffer += DEFAULT_SLIDER_HEIGHT;
    }

    SDL_RenderPresent( renderer);
	SDL_UpdateWindowSurface(sliderWindow->window);
}