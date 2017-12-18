/***
 * Traffic Signal Simulator
 * author: Joel Fuentes
 ***/

#ifndef TRAFFICSIGNALSIMULATOR_INTERSECTION_H
#define TRAFFICSIGNALSIMULATOR_INTERSECTION_H

/*
 * Represents an intersection between 2 roads. Maintains the status of traffic lights
 * for this intersection.
 */

class Intersection{
private:
  int status;
  int road1;
  int positionRoad1;
  int road2;
  int positionRoad2;
  int timeTrafficLight;
  int internalSteps;

public:
  Intersection(int sta, int r1, int posRoad1, int r2, int posRoad2, int time);

  ~Intersection();

  int getStatus();

  void setStatus(int s);

  void advance();

  int getInternalSteps();

  void setInternalSteps(int i);

  int getTimeTrafficLight();
};

#endif //TRAFFICSIGNALSIMULATOR_INTERSECTION_H
