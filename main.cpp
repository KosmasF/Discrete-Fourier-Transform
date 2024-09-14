extern "C"{
#include "dft.h"
}

#include "Graph.hxx"


int main()
{
    Graph graph(101);
    Wave wave = SinWaveByFreq(100, 201, 1, 0);
    DFT_data data = DiscreteFourierTranform(wave, 0, 101);
    for(int i = 0; i < data.maxFreq - data.minFreq; i++)
    {
        graph.Add(data.data[i].ampitude);
    }


    while(!Raylib::WindowShouldClose())
        graph.Draw();
   
   free(data.data);


    return 0;
}