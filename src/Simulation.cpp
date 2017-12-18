/***
 * Traffic Signal Simulator
 * author: Joel Fuentes
 ***/


#include "Simulation.h"
#include <iostream>
#include "ncurses.h"

Simulation::Simulation(int width, int height, int timeTrafficLights, bool man){
  this->width = width;
  this->height = height;
  map = (int **)malloc(height*sizeof(int*));
  for(int i = 0; i < height; i++){
    map[i] = (int*) malloc(width* sizeof(int));
  }

  // set all values to -1
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      map[i][j] = -1;
    }
  }

  timeForTrafficLights = timeTrafficLights;
  steps = 0;
  manual = man;
}

Simulation::~Simulation(){
  for(int i = 0; i < height; i++){
    free(map[i]);
  }
  free(map);

  for(Road *r: roads)
    delete r;
  for(Intersection *i: intersections)
    delete i;

}

bool Simulation::addRoad(int x, int y, int length, int orientation, int numCarsLeft, int numCarsRight){

  if(orientation == VERTICAL){
    //check if road fits on map
    if(y+length > height) {
      std::cout << "Error placing road: length of road is longer than allowed\n";
      return false;
    }

    // check whether road can be placed on map
    for(int i = 0; i < length; i++){
      if(map[x+i][y] != -1){
        // a road is placed on this position, check if it is horizontal
        Road *road = roads[map[x+i][y]];
        if(road->getOrientation() == VERTICAL){
          // can't be placed
          std::cout << "Error placing road: another road is placed on same orientation and position\n";
          return false;
        }else if(road->getOrientation() == HORIZONTAL){
          // avoid T corners
          if(road->getOriginY() == y){
            std::cout << "Error placing road: T corners are not allowed\n";
            return false;
          }
        }
      }
    }

    int index = roads.size();
    Road *r = new Road(x, y, length, orientation, numCarsLeft, numCarsRight);

    // add road on map with its intersections (if any)
    for(int i = 0; i < length; i++){
      if(map[x+i][y] != -1){
        //intersection
        Road *r2 = roads[map[x+i][y]];
        int pos2 = (y) - r2->getOriginY();
        Intersection *inter;
        if(manual){
          int time;
          std::cout << "\nIntersection found with Road " << map[x+i][y];
          std::cout << "\nEnter time for this intersection's Traffic Signal (between 3 and 10): ";
          std::cin >> time;
          inter = new Intersection(VERTICAL, index, i, map[x+i][y], pos2, time);
        }else
          inter = new Intersection(VERTICAL, index, i, map[x+i][y], pos2, 4);
        intersections.push_back(inter);
        // add intersection to road
        r->addIntersection(i, inter);
        r2->addIntersection(pos2, inter);
      }else {
        map[x+i][y] = index;
      }
    }

    roads.push_back(r);
  }

  if(orientation == HORIZONTAL){
    //check if road fits on map
    if(x+length > width) {
      std::cout << "length of road is longer than allowed\n";
      return false;
    }

    // check whether road can be placed on map
    for(int i = 0; i < length; i++){
      if(map[x][y+i] != -1){
        // a road is placed on this position, check if it is horizontal
        Road *road = roads[map[x][y+i]];
        if(road->getOrientation() == HORIZONTAL){
          // can't be placed
          std::cout << "Error placing road: another road is placed on same orientation and position\n";
          return false;
        }else if(road->getOrientation() == VERTICAL){
          // avoid T corners
          if(road->getOriginX() == x){
            std::cout << "Error placing road: T corners are not allowed\n";
            return false;
          }
        }
      }
    }

    int index = roads.size();
    Road *r = new Road(x, y, length, orientation, numCarsLeft, numCarsRight);

    // add road on map with its intersections (if any)
    for(int i = 0; i < length; i++){
      if(map[x][y+i] != -1){
        //intersection
        Road *r2 = roads[map[x][y+i]];
        int pos2 = (x) - r2->getOriginX();
        Intersection *inter;
        if(manual){
          int time;
          std::cout << "\nIntersection found with Road " << map[x][y+i];
          std::cout << "\nEnter time for this intersection's Traffic Signal (between 3 and 10): ";
          std::cin >> time;
          inter = new Intersection(HORIZONTAL, index, i, map[x][y+i], pos2, time);
        }else
          inter = new Intersection(HORIZONTAL, index, i, map[x][y+i], pos2, 4);
        intersections.push_back(inter);
        // add intersection to road
        r->addIntersection(i, inter);
        r2->addIntersection(pos2, inter);
      }else {
        map[x][y+i] = index;
      }
    }

    roads.push_back(r);

  }
  return true;
}

void Simulation::advance(){
  for(Road *road: roads){
    road->advance();
  }
  steps++;
    for(Intersection *inter: intersections){
      inter->advance();
      if(inter->getInternalSteps() == inter->getTimeTrafficLight()) {
        if (inter->getStatus() == VERTICAL) {
          inter->setStatus(HORIZONTAL);
        } else if (inter->getStatus() == HORIZONTAL) {
          inter->setStatus(VERTICAL);
        }
        inter->setInternalSteps(0);
      }
    }
}

int Simulation::getNumRoads(){
  return roads.size();
}

void Simulation::print(){

  for(Road *road: roads){
    if(road->getOrientation() == HORIZONTAL){
      int x = road->getOriginX()*2;
      int y = road->getOriginY()*2;
      for(int i = 0; i < road->getLength(); i++){
        Intersection *inter = road->getIntersection(i);

        if(inter != nullptr){
          if(inter->getInternalSteps() == inter->getTimeTrafficLight()-1 && inter->getStatus() == HORIZONTAL)
            attron(COLOR_PAIR(2));
          else if(inter->getStatus() == HORIZONTAL)
            attron(COLOR_PAIR(3));
          else
            attron(COLOR_PAIR(1));
        }
        if(road->hasCarFirstRoad(i)){
          mvprintw(x, y + (i * 2), "#");
          mvprintw(x, y + (i * 2 + 1), "#");
        }else {
          mvprintw(x, y + (i * 2), "-");
          mvprintw(x, y + (i * 2 + 1), "-");
        }

        if(road->hasCarSecondRoad(i)){
          mvprintw(x + 1, y + (i * 2), "#");
          mvprintw(x + 1, y + (i * 2 + 1), "#");
        }else {
          mvprintw(x + 1, y + (i * 2), "-");
          mvprintw(x + 1, y + (i * 2 + 1), "-");
        }

        if(inter != nullptr){
          if(inter->getInternalSteps() == inter->getTimeTrafficLight()-1&& inter->getStatus() == HORIZONTAL)
            attroff(COLOR_PAIR(2));
          else if(inter->getStatus() == HORIZONTAL)
            attroff(COLOR_PAIR(3));
          else
            attroff(COLOR_PAIR(1));
        }

      }
    }else if(road->getOrientation() == VERTICAL){
      int x = road->getOriginX()*2;
      int y = road->getOriginY()*2;
      for(int i = 0; i < road->getLength(); i++){
        Intersection *inter = road->getIntersection(i);

        if(inter != nullptr){
          if(inter->getInternalSteps() == inter->getTimeTrafficLight()-1 && inter->getStatus() == HORIZONTAL)
            attron(COLOR_PAIR(2));
          else if(inter->getStatus() == HORIZONTAL)
            attron(COLOR_PAIR(3));
          else
            attron(COLOR_PAIR(1));
        }

        if(road->hasCarFirstRoad(i)) {
          mvprintw(x + (i * 2), y, "#");
          mvprintw(x + (i * 2 + 1), y, "#");
        }else{
          mvprintw(x + (i * 2), y, "|");
          mvprintw(x + (i * 2 + 1), y, "|");
        }

        if(road->hasCarSecondRoad(i)) {
          mvprintw(x + (i * 2), y + 1, "#");
          mvprintw(x + (i * 2 + 1), y + 1, "#");
        }else{
          mvprintw(x + (i * 2), y + 1, "|");
          mvprintw(x + (i * 2 + 1), y + 1, "|");
        }

        if(inter != nullptr){
          if(inter->getInternalSteps() == inter->getTimeTrafficLight()-1 && inter->getStatus() == HORIZONTAL)
            attroff(COLOR_PAIR(2));
          else if(inter->getStatus() == HORIZONTAL)
            attroff(COLOR_PAIR(3));
          else
            attroff(COLOR_PAIR(1));
        }

      }
    }
  }
  mvprintw(44,0,"Status of traffic lights are shown for one road only");
  mvprintw(45,0,"Current time for traffic lights is %d steps", timeForTrafficLights);
  mvprintw(47,0,"Press c to advance one step");
  mvprintw(48,0,"Press e to exit");
  refresh();
}


