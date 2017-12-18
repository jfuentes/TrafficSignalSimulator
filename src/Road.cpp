/***
 * Traffic Signal Simulator
 * author: Joel Fuentes
 ***/

#include "Road.h"

Road::Road(int xx, int yy, int len, int orien, int carsLeft, int carsRight){
    x = xx;
    y = yy;
    length = len;
    orientation = orien;
    numCarsLeft = carsLeft;
    carsInLeft = 0;
    numCarsRight = carsRight;
    carsInRight = 0;
    road = (int **)malloc(3*sizeof(int*));
    for(int i = 0; i < 3; i++){
      road[i] = (int*) malloc(length* sizeof(int));
    }

    for(int i = 0; i < length; i++){
      road[0][i] = -1;
    }
    for(int i = 0; i < length; i++){
      road[1][i] = 0;
      road[2][i] = 0;
    }
  }

  Road::~Road(){
    for(int i = 0; i < 3; i++){
      free(road[i]);
    }
    free(road);
  }

  void Road::addIntersection(int position, Intersection *inter){
    road[0][position] = intersections.size();
    intersections.push_back(inter);
  }

  int Road::getOrientation(){
    return orientation;
  }

  int Road::getOriginX(){
    return x;
  }

  int Road::getOriginY(){
    return y;
  }

  int Road::getLength(){
    return length;
  }

  bool Road::hasCarFirstRoad(int i){
    return road[1][i] != 0;
  }

  bool Road::hasCarSecondRoad(int i){
    return road[2][i] != 0;
  }

  // advance one step
  void Road::advance(){
    // end to beginning (row 1)
    for(int i = length-1; i >0; i--){
      if(road[0][i] != -1){
        // intersection
        if(intersections[road[0][i]]->getStatus() != orientation){
          continue;
        }else{
          if(road[1][i] == 0 && road[1][i-1] == 1){
            // advance car
            road[1][i] = 1;
            road[1][i-1] = 0;
          }
        }
      }else{
        if(road[1][i] == 0 && road[1][i-1] == 1){
          // advance car
          road[1][i] = 1;
          road[1][i-1] = 0;
        }else if(road[1][i] == 1 && road[1][i-1] == 1 && i == length -1 ){
          // advance car
          road[1][i] = 1;
          road[1][i-1] = 0;
        }else if(road[1][i] == 1 && road[1][i-1] == 0 && i == length - 1){
          // advance car
          road[1][i] = 0;
        }
      }
    }

    // if there is any left car to add
    if(carsInLeft < numCarsLeft && road[1][0] == 0){
      road[1][0] = 1;
      carsInLeft++;
    }


    // end to beginning (row 2)
    for(int i = 0; i < length - 1; i++){
      if(road[0][i] != -1){
        // intersection
        if(intersections[road[0][i]]->getStatus() != orientation) {
          continue;
        }else  if(road[2][i] == 0 && road[2][i+1] == 1){
            // advance car
            road[2][i] = 1;
            road[2][i+1] = 0;
          }

      }else{
        if(road[2][i] == 0 && road[2][i+1] == 1){
          // advance car
          road[2][i] = 1;
          road[2][i+1] = 0;
        }else if(road[2][i] == 1 && road[2][i+1] == 1 && i == 0){
          // advance car
          road[2][i] = 1;
          road[2][i+1] = 0;
        }else if(road[2][i] == 1 && road[2][i+1] == 0 && i == 0){
          // advance car
          road[2][i] = 0;
        }
      }
    }

    // if there is any left car to add
    if(carsInRight < numCarsRight && road[2][length-1] == 0){
      road[2][length-1] = 1;
      carsInRight++;
    }
  }


Intersection *Road::getIntersection(int i){
  if(road[0][i] != -1)
    return intersections[road[0][i]];
  else
    return nullptr;
}
