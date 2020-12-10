/**
 * @file configuration_sim.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <ctime>
#include <random>

#include "src/config_manager.h"
#include "src/configuration_simulator.h"

int main(int argc, char**argv) {
  // note: this usage will change depending on
  //       how you build your config_sim classes
  //   E.g., how will you handle getting the length of simulation value?
  std::cout << "Usage: ./build/bin/configuration_sim <config_filename>";
  std::cout << '\n';

  // Check command line params for config file name
  int rounds = 50;
  int times = 5;
  srand((long)time(NULL));
  std::string filename;
  std::string default_filename = "config.txt";

  // check the user's input
  if (argc == 1) {  // if just on imput argument provided use all default values
    std::cout << "use the default file name" << '\n';
    filename = "config.txt";
    std::ifstream file("config/" + filename);
    // if cannot open file, report the error message then quit the program
    if (!file) {
      std::cout << "cannot open file" << '\n';
      exit(1);
    }
  } else if (argc > 1){  // check the different case for the proived input
    filename = argv[1];  // set the 1st input to the file name
    std::cout << "use the given file name" << '\n';
    // if the filename is invild, use the default one
    if (filename.compare(default_filename) != 0) {
      filename = default_filename;
    }
    if (argc == 2) {
      std::cout << "use the default value of length of simulation" << '\n';
      std::ifstream file("config/" + filename);
      if (!file) {
        std::cout << "cannot open file" << '\n';
        exit(1);
      }
    } else if (argc == 3) {
      std::cout << "use the given file name" << '\n';
      std::cout << "use the given value of length of simulation value" << '\n';
      filename = argv[1];
      std::cout << argv[1] << '\n';
      std::ifstream file("config/" + filename);
      rounds = atoi((argv[2]));
      if (!file) {
        std::cout << "cannot open file" << '\n';
        exit(1);
      }
      if (rounds < times) {
        std::cout << "please give value large than 5" << '\n';
        exit(1);
      }
    } else if (argc == 4) {
      std::cout << "use the given file name" << '\n';
      std::cout << "use the given value of length of simulation value" << '\n';
      std::cout << "use the given time" << '\n';
      filename = argv[1];
      std::cout << argv[1] << '\n';
      std::ifstream file("config/" + filename);
      rounds = atoi(argv[2]);
      times = atoi(argv[3]);
      if (!file) {
        std::cout << "cannot open file" << '\n';
        exit(1);
      }
      if (rounds < times || (rounds == 0 && times == 0)) {
        std::cout << "please give a vild value" << '\n';
        exit(1);
      }
  } else {
    exit(1);
    }
 }
  // if filename arg present
  //   Create ConfigManager
  //   Call ReadConfig
  //   Create ConfigurationSimulator
  //   Call Start on ConfigurationSimulator
  //   Start for loop, length of simulation (where from?)
  //     Call Update on ConfigurationSimulator
  // else
  //   echo info to the user about needing a config file name
  std::vector<int> busStartTimings;
  ConfigManager configM;
  configM.ReadConfig(filename);
  busStartTimings.push_back(times);
  ConfigurationSimulator config_sim = ConfigurationSimulator(&configM);


  std::cout << "/*************************" << '\n' << '\n';
  std::cout << "         STARTING" << '\n';
  std::cout << "        SIMULATION" << '\n';
  std::cout << "*************************/" << '\n';

  config_sim.Start(busStartTimings);

  std::cout << "/*************************" << '\n' << '\n';
  std::cout << "           BEGIN" << '\n';
  std::cout << "          UPDATING" << '\n';
  std::cout << "*************************/" << '\n';

  for (int i = 0; i < rounds; i++) {
	  config_sim.Update();
  }

  std::cout << "/*************************" << '\n' << '\n';
  std::cout << "        SIMULATION" << '\n';
  std::cout << "         COMPLETE" << '\n';
  std::cout << "*************************/" << '\n';
  return 0;
}
