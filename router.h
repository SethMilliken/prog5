// Author: Sutdents should put their names here.

#ifndef ROUTER_H
  #define ROUTER_H

#include "RouterRunner.h"

using namespace std;

class Router
{
private:
  int myWidth;
  int verticeCount;
  short **myMap;
  int minDistance(int dist[], bool sptSet[]);
  void dijkstra(int src);
  void printSolution(int dist[], int n);
  void printGraph(short **graph);
  void initializeGraphRow(short **graph, short row);
  void populateGraphForVertice(short **graph, short row, short col);

public:
  Router(short **map, int width);
  void findRoutes(const Coordinates *cityPos, int cityCount, Coordinates **paths, int pathCounts[]);
  void printMap();
};


#endif
