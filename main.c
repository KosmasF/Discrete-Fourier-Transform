#include "dft.h"
#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

bool WindowShouldClose() {
	SDL_Event e;

	while( SDL_PollEvent( &e ) != 0 ) {
		switch (e.type) {
			case SDL_QUIT:
				return true;
		}
	}

	return false;
}

int main()
{
	SDL_Init( SDL_INIT_EVERYTHING );


    struct Wave wave = SinWaveByFreq(100, 201 , 1 , 0);
    struct DFT_data data = DiscreteFourierTranform(wave, 80 , 110, 1, false);
    struct Graph* graph = malloc(sizeof(struct Graph));

    graphSetMaxValues(graph, 1000);   
    graphSetupWindow(graph, "Ampitude Fourier Tranform", 1920 / 2 , 1080 / 2); 

    for(int i = 0; i < data.maxFreq - data.minFreq; i++)
    {
        graphAddValue(graph, data.data[i].ampitude);
    }

    graphDraw(graph);
    free(data.data);
    free(graph);

    while(!WindowShouldClose());
   

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