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
    int ret;
	ret = SDL_Init( SDL_INIT_EVERYTHING );


    float testWaveFreq = 100;
    float testWaveSampleRate = 201;
    float minFreq = 80;
    float maxFreq = 110;
    float increment = 1;
    graph = malloc(sizeof(struct Graph));
    sliderWindow = malloc(sizeof(struct SliderWindow));

    graphSetMaxValues(graph, 1000);   
    graphSetupWindow(graph, "Ampitude Fourier Tranform", 1920 / 2 , 1080 / 2); 

    SliderWindowSetup(sliderWindow, "Sliders", 5, 500, 24);
    SliderSetup(sliderWindow, 0, 0, 200, "testWaveFreq", &testWaveFreq);
    SliderSetup(sliderWindow, 1, 1, 402, "testWaveSampleRate", &testWaveSampleRate);
    SliderSetup(sliderWindow, 2, 0, 1000, "minFreq", &minFreq);
    SliderSetup(sliderWindow, 3, 0, 1000, "maxFreq", &maxFreq);
    SliderSetup(sliderWindow, 4, 1, 100, "increment", &increment);

    int i = 0;
    while(Loop())
    {
        struct Wave wave = SinWaveByFreq(testWaveFreq, testWaveSampleRate , 1 , 0);
        struct DFT_data data = DiscreteFourierTranform(wave, minFreq , maxFreq, increment, false);

        graphDestroy(graph);
        graphSetMaxValues(graph, 1000);   
        for(int i = 0; i < data.maxFreq - data.minFreq; i++)
        {
            graphAddValue(graph, data.data[i].ampitude);
        }

        graphDraw(graph);
        if(sliderWindow != NULL)
            SliderWindowDraw(sliderWindow);
        free(data.data);
        free(wave.data);
    i++;
        printf("%d\n",i);
    }

   




    graphDestroy(graph);
    graphDestroyWindow(graph);
    if(sliderWindow != NULL)
        SliderWindowClose(sliderWindow);
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