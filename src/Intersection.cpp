/***
 * Traffic Signal Simulator
 * author: Joel Fuentes
 ***/

#include "Intersection.h"

Intersection::Intersection(int sta, int r1, int posRoad1, int r2, int posRoad2, int time):
  status(sta), road1(r1), positionRoad1(posRoad1), road2(r2), positionRoad2(posRoad2),
  timeTrafficLight(time), internalSteps(0){

}

Intersection::~Intersection(){}

int Intersection::getStatus() {
  return status;
}

void Intersection::setStatus(int s) {
  status = s;
}

void Intersection::advance() {
  internalSteps++;
}

int Intersection::getInternalSteps(){
  return internalSteps;
}

void Intersection::setInternalSteps(int i){
  internalSteps = i;
}

int Intersection::getTimeTrafficLight(){
  return timeTrafficLight;
}
