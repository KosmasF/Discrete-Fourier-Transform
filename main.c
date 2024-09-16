#include "dft.h"
#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "Slider.h"

struct Graph* graph;
struct SliderWindow* sliderWindow;


bool Loop() {
	SDL_Event e;

	while( SDL_PollEvent( &e ) != 0 ) {
        if(e.type == SDL_QUIT)
        {
            return false;
        }
        else if( e.type == SDL_WINDOWEVENT)
        {
            if(e.window.windowID == SDL_GetWindowID(graph->window.window))
            {
                if(e.window.event == SDL_WINDOWEVENT_CLOSE)
                    return false;
            }
            else if(sliderWindow != NULL)
            {
                if(e.window.windowID == SDL_GetWindowID(sliderWindow->window))
                {
                    if(e.window.event == SDL_WINDOWEVENT_CLOSE)
                    {
                        SliderWindowClose(sliderWindow);
                        sliderWindow = NULL;
                    }
                }
            }

		}
        else if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
        {
            if(e.button.windowID == SDL_GetWindowID(graph->window.window))
            {
                ;
            }
            else if(e.button.windowID == SDL_GetWindowID(sliderWindow->window))
            {
                SliderWindowHandleEvent(sliderWindow, &e);
            }
        }
        else if(e.type == SDL_MOUSEMOTION)
        {
            if(e.button.windowID == SDL_GetWindowID(graph->window.window))
            {
                ;
            }
            else if(e.button.windowID == SDL_GetWindowID(sliderWindow->window))
            {
                SliderWindowHandleEvent(sliderWindow, &e);
            }            
        }
	}

    return true;
}

int main()
{
	SDL_Init( SDL_INIT_EVERYTHING );


    struct Wave wave = SinWaveByFreq(100, 201 , 1 , 0);
    struct DFT_data data = DiscreteFourierTranform(wave, 80 , 110, 1, false);
    graph = malloc(sizeof(struct Graph));
    sliderWindow = malloc(sizeof(struct SliderWindow));

    graphSetMaxValues(graph, 1000);   
    graphSetupWindow(graph, "Ampitude Fourier Tranform", 1920 / 2 , 1080 / 2); 

    float test;
    SliderWindowSetup(sliderWindow, "Sliders", 1, 200);
    SliderSetup(sliderWindow, 0, 0, 1, "Test", &test);

    for(int i = 0; i < data.maxFreq - data.minFreq; i++)
    {
        graphAddValue(graph, data.data[i].ampitude);
    }

    while(Loop())
    {
        graphDraw(graph);
        if(sliderWindow != NULL)
            SliderWindowDraw(sliderWindow);
    }

   

    graphDestroy(graph);
    graphDestroyWindow(graph);
    if(sliderWindow != NULL)
        SliderWindowClose(sliderWindow);

    free(data.data);
    free(graph);
    SDL_Quit();
    return 0;
}

/*
    int numSamples = sizeof(RecData) / sizeof(double);

    //for(int i = 0; i < 20;i++)
    //{
    printf("Creating wave...\n");
    float sampleRate = numSamples / (duration * US);
    Wave wave = {RecData, sampleRate, 1000 * US};
    printf("Calculating Discrete fourier transform...\n");
    const int minFreq = 90*MHZ;
    const int maxFreq = 91*MHZ;
    const int increment = (maxFreq - minFreq) / 1920.f / 2;
    DFT_data data = DiscreteFourierTranform(wave, minFreq, maxFreq, increment, true);
    printf("Adding data to graph...\n");
    Graph graph((maxFreq - minFreq) / increment);
    for(int i = 0; i < (maxFreq - minFreq) / increment; i++)
    {
        graph.Add(data.data[i].ampitude);
    }
    printf("Displaying graph...\n");
    graph.Draw();
   free(data.data);
    //}

    while(!Raylib::WindowShouldClose())
        graph.Draw();
   


    return 0;*/