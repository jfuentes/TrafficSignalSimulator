/***
 * Traffic Signal Simulator
 * author: Joel Fuentes
 ***/

#ifndef TRAFFICSIGNALSIMULATOR_SIMULATION_H
#define TRAFFICSIGNALSIMULATOR_SIMULATION_H

#include "Road.h"
#include "Intersection.h"
#include <vector>

#define VERTICAL 1
#define HORIZONTAL 2

/*
 * Manages the entire simulation by maintaining a 2D map with roads and intersections
 */

class Simulation{
private:
  int **map;
  std::vector<Road*> roads;
  std::vector<Intersection*> intersections;

  // settings
  int timeForTrafficLights; // number of steps a traffic light (red, yellow, green) will last
  // yellow light always lasts 1 step

  int width;
  int height;
  int steps;
  bool manual;

public:
  Simulation(int width, int height, int timeTrafficLights, bool man);

  ~Simulation();

  bool addRoad(int x, int y, int length, int orientation, int numCarsLeft, int numCarsRight);

  void advance();

  void print();

  int getNumRoads();

};

#endif //TRAFFICSIGNALSIMULATOR_SIMULATION_H
