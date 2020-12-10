#include <iostream>
#include <random>
#include <ctime>

#include "passenger.h"
#include "passenger_factory.h"

int main() {
  // std::ofstream myfile;
  // myfile.open("capture_transit_sim.txt");

  srand((long)time(NULL)); //Seed the random number generator...

  myfile << "Let's begin..." << std::endl;
  int current = 1;
  int end = 20;
  Passenger * tmp = NULL;

  myfile << "Entering loop..." << std::endl;

  for (int i = 0; i < 100; i++) {
    myfile << "Making Passenger #" << i << std::endl;
    tmp = PassengerFactory::Generate(current, end);
    myfile << "Reporting: " << std::endl;
    tmp->Report(myfile);

    delete tmp;
  }

  myfile << "After loop..." << std::endl;
  //myfile.close();
  return 0;
}
