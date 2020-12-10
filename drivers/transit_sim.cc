#include <ctime>
#include <iostream>
#include <random>

#include "local_simulator.h"

int main() {

  int rounds = 50; //Number of rounds of generation to simulate in test

  srand((long)time(NULL)); //Seed the random number generator...

  LocalSimulator my_sim;
  std::ofstream myfile;
  myfile.open("transit_sim.txt");

  myfile << "/*************************" << std::endl << std::endl;
  myfile << "         STARTING" << std::endl;
  myfile << "        SIMULATION" << std::endl;
  myfile << "*************************/" << std::endl;

  my_sim.Start();

  myfile << "/*************************" << std::endl << std::endl;
  myfile << "           BEGIN" << std::endl;
  myfile << "          UPDATING" << std::endl;
  myfile << "*************************/" << std::endl;

  for (int i = 0; i < rounds; i++) {
	  my_sim.Update();
  }

  myfile << "/*************************" << std::endl << std::endl;
  myfile << "        SIMULATION" << std::endl;
  myfile << "         COMPLETE" << std::endl;
  myfile << "*************************/" << std::endl;

  myfile.close();
  return 0;
}
