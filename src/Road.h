/***
 * Traffic Signal Simulator
 * author: Joel Fuentes
 ***/

#ifndef TRAFFICSIGNALSIMULATOR_ROAD_H
#define TRAFFICSIGNALSIMULATOR_ROAD_H

#include "Intersection.h"
#include <vector>

/*
 * Represents a 2-way road. Contains also information about cars and intersections.
 */

class Road{
private:
  int x; // starting point
  int y;
  /*
   * first row = intersections
   * second row = 1-way road
   * third row = 1-way road (opposite direction)
   */
  int **road;
  int length;
  int orientation; // 1: vertical, 2:horizontal
  int numCarsLeft;
  int carsInLeft;
  int numCarsRight;
  int carsInRight;
  std::vector<Intersection*> intersections;

public:
  Road(int xx, int yy, int len, int orien, int carsLeft, int carsRight);

  ~Road();

  void addIntersection(int position, Intersection *inter);

  int getOrientation();

  int getOriginX();

  int getOriginY();

  int getLength();

  void advance();

  bool hasCarFirstRoad(int i);

  bool hasCarSecondRoad(int i);

  Intersection *getIntersection(int i);

};

#endif //TRAFFICSIGNALSIMULATOR_ROAD_H
