/***
 * Traffic Signal Simulator
 * author: Joel Fuentes
 ***/

#include <iostream>
#include "src/Simulation.h"
#include "ncurses.h"


int main() {
  int option;
  do {
    // Main menu
    std::cout << "*** Traffic Signal Simulator ***\n";
    std::cout << "1.- Enter map manually\n";
    std::cout << "2.- Run pre-loaded map\n";
    std::cout << "3.- Exit\n";
    std::cout << "Option: ";

    std::cin >> option;
  }while(option < 1 || option > 3);

  if(option == 3)
    return 0;


  Simulation *sim;
  if(option == 2) {
    sim = new Simulation(100, 100, 4, false);
    sim->addRoad(3, 1, 17, HORIZONTAL, 20, 15);
    sim->addRoad(1, 4, 20, VERTICAL, 3, 6);
    sim->addRoad(0, 12, 19, VERTICAL, 15, 10);
    sim->addRoad(17, 2, 20, HORIZONTAL, 3, 5);
    sim->addRoad(7, 8, 25, HORIZONTAL, 3, 8);
    sim->addRoad(12, 0, 27, HORIZONTAL, 5, 5);
    sim->addRoad(9, 18, 12, VERTICAL, 10, 10);
    sim->addRoad(5, 21, 10, VERTICAL, 8, 8);
  }else if(option ==1){
    // map
    int width, height, numRoads, x, y, length, orientation, numCarsLeft, numCarsRight;
    std::cout << "Enter map dimensions (positive values)\n";
    std::cout << "width: ";
    std::cin >> width;
    std::cout << "\nheight: ";
    std::cin >> height;
    sim = new Simulation(width, height, 4, true);

    // roads
    std::cout << "\nNumber of Roads: ";
    std::cin >> numRoads;
    for(int i = 0; i < numRoads; i++){
      std::cout << "\n\n** Road " << (i+1) << " **";
      std::cout << "\nStarting point x: ";
      std::cin >> x;
      std::cout << "\nStarting point y: ";
      std::cin >> y;
      std::cout << "\nLength: ";
      std::cin >> length;
      std::cout << "\nOrientation (1: Horizontal, 2: Vertical): ";
      std::cin >> orientation;
      std::cout << "\nNumber of Cars (from left): ";
      std::cin >> numCarsLeft;
      std::cout << "\nNumber of Cars (from right): ";
      std::cin >> numCarsRight;
      if(sim->addRoad(x, y, length, (orientation==1 ? HORIZONTAL : VERTICAL), numCarsLeft, numCarsRight))
        std::cout << "\nRoad added with ID " << (sim->getNumRoads()-1);

    }
  }

  if(sim == nullptr)
    return 1;

  initscr();
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_RED);
  init_pair(2, COLOR_WHITE, COLOR_YELLOW);
  init_pair(3, COLOR_WHITE, COLOR_GREEN);

  clear();
  sim->print();
  getch();
  int c;
  do {
    sim->advance();
    clear();
    sim->print();
    c = getch();
  }while(c == 'c');
  endwin();

  delete sim;
  return 0;
}