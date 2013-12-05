// Author Sean Davis
#include "router.h"
#include <iostream>
#include <stdio.h>
#include <limits.h>

using namespace std;

Router::Router(short **map, int width)
{
   myWidth = width;
   verticeCount = myWidth * myWidth;

   cout << "initializing array..." << endl;
   myMap = new short* [width];
   cout << "initializing subarrays..." << endl;
   for(int row = 0; row < width; row++)
   {
       cout << "initializing row " << row << "..." << endl;
       myMap[row] = new short[width];
       for(int col = 0; col < width; col++)
       {
           (myMap)[row][col] = (map)[row][col];
       }
   }
   cout << endl;
   printMap();

} // Router()

void Router::printMap()
{
   cout << "I am a Router and here is my map of width " << myWidth << ":" << endl;
   for(int row = 0; row < myWidth; row++)
   {
       for(int col = 0; col < myWidth; col++)
       {
           cout << (myMap)[row][col] << " ";
       }
       cout << endl;
   }
   cout << endl;
}

void Router::printGraph(short **graph)
{
   cout << "The graph of my map is this:" << endl;
   for(int row = 0; row < verticeCount; row++)
   {
       for(int col = 0; col < verticeCount; col++)
       {
          printf("%3d ", (graph)[row][col]);
       }
       cout << endl;
   }
   cout << endl;
}

int Router::minDistance(int dist[], bool sptSet[])
{
    int min = INT_MAX;
    int min_index;

    for(int v = 0; v < (myWidth * myWidth); v++)
    {
        if (sptSet[v] == false && dist[v] <= min)
        {
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}

void Router::dijkstra(int src)
{
    cout << "dijkstra algorithm begin..." << endl;
    //int* dist;
    int* dist = new int [myWidth];
    bool* sptSet = new bool [myWidth];

    for (int i = 0; i < myWidth; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < myWidth - 1; count++)
    {
        int u = minDistance(dist, sptSet);
        cout << "min distance: " << u << endl;
        sptSet[u] = true;

        for(int v = 0; v < myWidth; v++)
        {
            if (!sptSet[v])
            //if (!sptSet[v] && (myMap)[u][v])
            //if (!sptSet[v] && (myMap)[u][v] && dist[u] != INT_MAX && dist[u] + (myMap)[u][v] < dist[v])
            {
    //            dist[v] = dist[u] + myMap[u][v];
            }
        }
    }
}

void Router::printSolution(int dist[], int n)
{
       printf("Vertex   Distance from Source\n");
          for (int i = 0; i < myWidth; i++)
                    printf("%d \t\t %d\n", i, dist[i]);
}

void Router::initializeGraphRow(short **graph, short row)
{
    cout << "initializing graph row " << row << "..." << endl;
    graph[row] = new short[verticeCount];
    for(int col = 0; col < verticeCount; col++)
    {
        (graph)[row][col] = 0;
    }
}

void Router::populateGraphForVertice(short **graph, short row, short col)
{
    int index = (row * myWidth) + (col % myWidth);
    cout << "populating graph for vertice " << row << ", " << col << " (" << index << ")" << endl;
    int r = 0;
    int c = 0; 
    for(int count = 0; count < verticeCount; count++)
    {
        if (count != 0)
        {
            r = count / myWidth;
            c = count % myWidth;
        }
        //cout << "testing " << r << ", " << c << endl;
          //  << " for " << row << ", " << col << endl;

        if (row == r - 1 || row == r + 1 || row == r)
        {
            if (col == c - 1 || col == c + 1 || col == c)
            {
                if (!(row == r && col == c)
                        && !(row == r - 1 && col == c - 1)
                        && !(row == r - 1 && col == c + 1)
                        && !(row == r + 1 && col == c - 1)
                        && !(row == r + 1 && col == c + 1)
                   ) 
                {
                    (graph)[index][count] = myMap[r][c];
                    //cout << "node " << r << ", " << c << " adjacent (" << myMap[r][c] << ")" << endl;
                }
            }
        }
    }
}

void Router::findRoutes(const Coordinates *cityPos, int cityCount, 
  Coordinates **paths, int pathCounts[])
{
   cout << "I can haz route finding..." << endl;
   short **graph;
   graph = new short* [verticeCount];
   for(int row = 0; row < verticeCount; row++)
   {
       initializeGraphRow(graph, row);
   }
   for(int count = 0; count < verticeCount; count++)
   {
       int row = 0;
       int col = 0; 
       if (count != 0)
       {
           row = count / myWidth;
           col = count % myWidth;
       }
       populateGraphForVertice(graph, row, col);
   }
   printGraph(graph);
   //dijkstra(0);

} // findRoutes()


