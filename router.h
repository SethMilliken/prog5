// Author: Sutdents should put their names here.

#ifndef ROUTER_H
  #define ROUTER_H

#include "RouterRunner.h"

using namespace std;

class Router
{
public:
  Router(short **map, int width);
  void findRoutes(const Coordinates *cityPos, int cityCount, Coordinates **paths, int pathCounts[]);
};


#endif
